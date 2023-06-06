#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
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
    sql = "INSERT INTO QUIZ (NAME,AGE,ADDRESS,SALARY) "
          "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

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
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " return JSValueMakeString(context, string);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Records created successfully\n");
    }
}

static JSValueRef addanswer(JSContextRef context,
                            JSObjectRef function,
                            JSObjectRef thisObject,
                            size_t argumentCount,
                            const JSValueRef arguments[],
                            JSValueRef *exception)
{

    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    sql = "{INSERT INTO QUIZ (lib) "
          "VALUES (" +
          jsc_value_to_string(arguments[0]) + "); "
          /* Execute SQL statement */
          rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

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

static JSValueRef getquizs(JSContextRef context,
                           JSObjectRef function,
                           JSObjectRef thisObject,
                           size_t argumentCount,
                           const JSValueRef arguments[],
                           JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

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

//
//  Boilerplate code / signal callback for attaching methods when a
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

    JSStringRef function_name = JSStringCreateWithUTF8CString("whatever");
    JSObjectRef boiler_plate = JSObjectMakeFunctionWithCallback(js_ctx,
                                                                function_name,
                                                                some_method);
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
                        JSStringCreateWithUTF8CString("getquiz"),
                        boiler_plate,
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
        rc = sqlite3_exec(db, buffer, NULL, 0, NULL);
    }
    g_signal_connect(webkit_script_world_get_default(),
                     "window-object-cleared",
                     G_CALLBACK(window_object_cleared_callback),
                     NULL);
}