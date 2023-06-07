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

class Quiz
{
    std::string id;
    std::string name;

public:
    Quiz() {}
    Quiz(std::string n, std::string i)
    {
        id = i;
        name = n;
    }
    std::string getname() { return name; }
    std::string getid() { return id; }
};
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
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    char *sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
                "VALUES (1, 'Paul', 32, 'California', 20000.00 ); ";

    /* Execute SQL statement */
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

static JSValueRef addanswer(JSContextRef context,
                            JSObjectRef function,
                            JSObjectRef thisObject,
                            size_t argumentCount,
                            const JSValueRef arguments[],
                            JSValueRef *exception)
{

    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    char *sql = "{INSERT INTO QUIZ (lib) "
                "VALUES (' 3 '); ";
    /* Execute SQL statement */
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

static JSValueRef some_method(JSContextRef context,
                              JSObjectRef function,
                              JSObjectRef thisObject,
                              size_t argumentCount,
                              const JSValueRef arguments[],
                              JSValueRef *exception)
{
    int rc;
    JSStringRef string = JSStringCreateWithUTF8CString("butts");

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

int x;
std::vector<Quiz> quizs;
static int callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    quizs.push_back(Quiz(std::string(argv[0]), std::string(argv[1])));

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    x = i;
    printf("\n");
    return 0;
}

static JSValueRef getquizs(JSContextRef context,
                           JSObjectRef function,
                           JSObjectRef thisObject,
                           size_t argumentCount,
                           const JSValueRef arguments[],
                           JSValueRef *exception)
{

    quizs.clear();
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    /* Execute SQL statement */
    char *sql = "SELECT * from quiz";

    /* Execute SQL statement */
    int rc = sqlite3_exec(db, sql, callback, NULL, NULL);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
    JSObjectRef array = JSObjectMakeArray(context, 0, NULL, NULL);
    for (int i = 0; i < quizs.size(); i++)
    {
        JSObjectRef dict = JSObjectMake(context, NULL, NULL);
        JSStringRef key = JSStringCreateWithUTF8CString("id");
        JSStringRef value = JSStringCreateWithUTF8CString(quizs[i].getid().c_str());
        JSStringRef namekey = JSStringCreateWithUTF8CString("name");
        JSStringRef name = JSStringCreateWithUTF8CString(quizs[i].getname().c_str());
        JSObjectSetProperty(context, dict, key, JSValueMakeString(context, value), kJSPropertyAttributeNone, NULL);
        JSObjectSetProperty(context, dict, namekey, JSValueMakeString(context, name), kJSPropertyAttributeNone, NULL);
        JSObjectSetPropertyAtIndex(context, array, i, (JSValueRef)dict, NULL);
    }

    return array;
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

    JSObjectRef boiler_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                                NULL,
                                                                some_method);

    JSObjectRef getquizs_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                                  NULL,
                                                                  getquizs);
    JSValueRef exception = 0;
    JSObjectRef global = JSContextGetGlobalObject(js_ctx);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("myCFunction"),
                        boiler_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("addquiz"),
                        boiler_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("addquestion"),
                        boiler_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("addanswer"),
                        boiler_plate,
                        kJSPropertyAttributeDontDelete | kJSPropertyAttributeReadOnly,
                        &exception);
    JSObjectSetProperty(js_ctx,
                        global,
                        JSStringCreateWithUTF8CString("getallquiz"),
                        getquizs_plate,
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