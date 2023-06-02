#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>
#include <filesystem>
using std::string;
using std::filesystem::current_path;
static JSValueRef my_function(JSContextRef ctx, JSObjectRef function, JSObjectRef this_object, size_t argument_count, const JSValueRef arguments[], JSValueRef *exception)
{
    printf("test");
    std::cout << "test" << std::endl;
}
static void
web_view_javascript_finished(GObject *object,
                             GAsyncResult *result,
                             gpointer user_data)
{
    WebKitJavascriptResult *js_result;
    JSValueRef value;
    JSGlobalContextRef context;
    GError *error = NULL;

    js_result = webkit_web_view_run_javascript_finish(WEBKIT_WEB_VIEW(object), result, &error);
    if (!js_result)
    {
        g_warning("Error running javascript: %s", error->message);
        g_error_free(error);
        return;
    }
}
int main(int argc, char *argv[])
{
    // Initialize GTKmm
    Gtk::Main kit(argc, argv);

    // Create a new window
    Gtk::Window window;

    // Create a new WebView widget
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    auto webview_widget = Glib::wrap(GTK_WIDGET(webView));
    // Add the WebView to the window
    window.add(*webview_widget);
    std::cout << current_path() << std::endl;
    // Load a webpage
    auto web_ctx = webkit_web_context_get_default();
    auto module_path = g_build_filename(g_get_current_dir(),
                                        "modules/",
                                        NULL);
    std::cout << "MODULE LOAD PATH: " << module_path << "\n";
    webkit_web_context_set_web_extensions_directory(web_ctx, module_path);
    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webView));
    webkit_settings_set_enable_webgl(settings, true);
    webkit_settings_set_enable_developer_extras(settings, true);
    g_object_set(settings, "enable-javascript", TRUE, NULL);

    // Création d'un contexte JavaScript
    JSGlobalContextRef js_context = webkit_web_view_get_javascript_global_context(webView);

    // Création d'un objet JavaScript pour la fonction C
    JSObjectRef my_function_object = JSObjectMakeFunctionWithCallback(js_context, NULL, my_function);

    // Ajout de l'objet à l'objet global JavaScript
    JSStringRef my_function_name = JSStringCreateWithUTF8CString("myFunction");
    JSObjectSetProperty(js_context, JSContextGetGlobalObject(js_context), my_function_name, my_function_object, kJSPropertyAttributeNone, NULL);
    JSStringRelease(my_function_name);
    // Set the window size
    webkit_web_view_run_javascript(webView, "myFunction", NULL, web_view_javascript_finished, NULL);
    std::string url = string("file://") + current_path().string() + string("/ui/ressources/index.html");
    std::cout << url << std::endl;
    webkit_web_view_load_uri(webView, url.c_str());
    window.set_size_request(800, 600);
    // webkit_web_view_run_javascript(webV  JSObjectRef globalObject;

    // Show the window and start the main loop
    window.show_all();
    Gtk::Main::run(window);
    return 0;
}