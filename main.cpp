#include <gtkmm.h>
#include <webkit2/webkit2.h>

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

    // Load a webpage
    webkit_web_view_load_uri(webView, "https://www.google.com/");

    // Set the window size
    window.set_size_request(800, 600);
    // webkit_web_view_run_javascript(webV  JSObjectRef globalObject;

    // Show the window and start the main loop
    window.show_all();
    Gtk::Main::run(window);
    return 0;
}