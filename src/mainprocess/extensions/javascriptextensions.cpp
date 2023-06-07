#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <vector>
//
//  Some basic c function to be exposed to the javascript environment
//

sqlite3 *db;
char *zErrMsg = 0;

static JSValueRef addquiz(JSContextRef context,
                          JSObjectRef function,
                          JSObjectRef thisObject,
                          size_t argumentCount,
                          const JSValueRef arguments[],
                          JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    char *sql = "INSERT INTO QUIZ (NAME,AGE,ADDRESS,SALARY) "
                "VALUES (1, 'Paul', 32, 'California', 20000.00 ); ";

    int rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    return JSValueMakeString(context, string);
}

static JSValueRef addquestion(JSContextRef context,
                              JSObjectRef function,
                              JSObjectRef thisObject,
                              size_t argumentCount,
                              const JSValueRef arguments[],
                              JSValueRef *exception)
{

    JSStringRef string = JSValueToStringCopy(context, arguments[0], NULL);

    std::cout << "add a new question" << std::endl;

    char *qid = new char[10];
    JSStringGetUTF8CString(string, qid, 10);
    JSObjectRef arr = JSValueToObject(context, arguments[2], NULL);
    JSPropertyNameArrayRef propertyNames = JSObjectCopyPropertyNames(context, arr);
    size_t count = JSPropertyNameArrayGetCount(propertyNames);

    char *qlib = new char[100];
    JSStringGetUTF8CString(JSValueToStringCopy(context, arguments[1], NULL), qlib, 100);

    std::string sqlq = "INSERT INTO question (quizid,lib) "
                       "VALUES (" +
                       std::string(qid) + ",\"" + std::string(qlib) + "\"); ";

    for (size_t i = 0; i < count; ++i)
    {
        JSStringRef propertyName = JSPropertyNameArrayGetNameAtIndex(propertyNames, i);
        JSValueRef value = JSObjectGetPropertyAtIndex(context, arr, i, NULL);
        std::cout << "in" << std::endl;
        char *qlib = new char[100];
        JSStringGetUTF8CString(JSValueToStringCopy(context, value, NULL), qlib, 100);
        if (std::string(qlib) != "")
        {
            std::string sqlr = "INSERT INTO answer (questionid,lib) "
                               "VALUES (" +
                               std::string(qid) + ",\"" +
                               std::string(qlib) + "\"); ";
            // Do something with the value
            sqlite3_exec(db, sqlr.c_str(), NULL, 0, &zErrMsg);
        }
    }

    int rc = sqlite3_exec(db, sqlq.c_str(), NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }

    return JSValueMakeBoolean(context, true);
}

struct dataarray
{
    JSContextRef ctx;
    JSObjectRef array;
    std::string h;
};

static int sqlcallback(void *data, int argc, char **argv, char **azColName)
{
    dataarray *d = (dataarray *)data;
    std::cout << d->h.c_str() << "ok" << std::endl;
    printf("%s", d->h.c_str());
    JSObjectRef dict = JSObjectMake(d->ctx, NULL, NULL);

    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        JSStringRef key = JSStringCreateWithUTF8CString(azColName[i]);
        JSStringRef value = JSStringCreateWithUTF8CString(argv[i] ? argv[i] : "NULL");
        JSObjectSetProperty(d->ctx, dict, key, JSValueMakeString(d->ctx, value), kJSPropertyAttributeNone, NULL);
    }

    JSPropertyNameArrayRef propertyNames = JSObjectCopyPropertyNames(d->ctx, d->array);
    size_t i = JSPropertyNameArrayGetCount(propertyNames);

    JSObjectSetPropertyAtIndex(d->ctx, d->array, i, dict, NULL);

    printf("\n");
    return 0;
}

static JSValueRef sql(JSContextRef context,
                      JSObjectRef function,
                      JSObjectRef thisObject,
                      size_t argumentCount,
                      const JSValueRef arguments[],
                      JSValueRef *exception)
{

    dataarray *d = new dataarray;
    char *sql = new char[200];
    JSStringGetUTF8CString(JSValueToStringCopy(context, arguments[0], NULL), sql, 100);
    d->ctx = context;
    d->array = JSObjectMakeArray(context, 0, NULL, NULL);
    d->h = "yo";
    /* Execute SQL statement */

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql, sqlcallback, d, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "you got all quiz\n");
    }

    return d->array;
}
//
//  Boilerplate code / signal NULL for attaching methods when a
//  new javascript context is created.
//
static void
window_object_cleared_callback(WebKitScriptWorld *world,
                               WebKitWebPage *web_page,
                               WebKitFrame *frame,
                               gpointer user_data)
{
    std::cout << "attempting to set up custom c function bindings\n";
    JSGlobalContextRef js_ctx;
    js_ctx = webkit_frame_get_javascript_context_for_script_world(frame, world);

    JSObjectRef addquestion_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                                     NULL,
                                                                     addquestion);
    JSObjectRef sql_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                             NULL,
                                                             sql);

    JSValueRef exception = 0;
    JSObjectRef global = JSContextGetGlobalObject(js_ctx);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("sql"),
                        sql_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);

    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("addquestion"),
                        addquestion_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);

    if (exception)
    {
        std::cout << "Argh! an exception!!!!\n";
    }
}

//
//  Extension initialization thing.
//
extern "C" G_MODULE_EXPORT void
webkit_web_extension_initialize(WebKitWebExtension *extension)
{
    std::cout << "EXTENSION INITIALIZED\n";
    int rc = sqlite3_open("quizy.db", &db);
    if (rc)
    {
        std::cout << "Can't open database\n";
    }
    else
    {
        std::cout << "Open database successfully\n";
        std::ifstream database;
        int length;
        database.open("db.sql");
        database.seekg(0, std::ios::end);
        length = database.tellg();
        database.seekg(0, std::ios::beg);
        char *buffer = new char[length];
        database.read(buffer, length);
        char *err;
        rc = sqlite3_exec(db, buffer, NULL, 0, &err);
        printf("Error: %s\n", err);
    }
    g_signal_connect(webkit_script_world_get_default(),
                     "window-object-cleared",
                     G_CALLBACK(window_object_cleared_callback),
                     NULL);
}