#include <webkit2/webkit-web-extension.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>
#include <fstream>
#include <sqlite3.h>
//
//  Some basic c function to be exposed to the javascript environment
//

sqlite3 *db;

static JSValueRef addquestion(JSContextRef context,
                              JSObjectRef function,
                              JSObjectRef thisObject,
                              size_t argumentCount,
                              const JSValueRef arguments[],
                              JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
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
    return JSValueMakeString(context, string);
}
static JSValueRef addquiz(JSContextRef context,
                          JSObjectRef function,
                          JSObjectRef thisObject,
                          size_t argumentCount,
                          const JSValueRef arguments[],
                          JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
    return JSValueMakeString(context, string);
}

static JSValueRef some_method(JSContextRef context,
                              JSObjectRef function,
                              JSObjectRef thisObject,
                              size_t argumentCount,
                              const JSValueRef arguments[],
                              JSValueRef *exception)
{
    JSStringRef string = JSStringCreateWithUTF8CString("butts");
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
                        NULL,
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
        // char *buffer = new char[length];
        // database.read(buffer, length);
        // rc = sqlite3_exec(db, buffer, NULL, 0, NULL);
    }
    g_signal_connect(webkit_script_world_get_default(),
                     "window-object-cleared",
                     G_CALLBACK(window_object_cleared_callback),
                     NULL);
}