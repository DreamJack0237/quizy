#include "Webview.h"

View::View(string title)
{
    std::ifstream settingfile("setting", std::ios::app);

    char debug = settingfile.get();
    // Create a new WebView widget
    webview = WEBKIT_WEB_VIEW(webkit_web_view_new());

    auto webview_widget = Glib::wrap(GTK_WIDGET(webview));

    this->add(*webview_widget);
    std::cout << current_path() << std::endl;
    // Load a webpage
    auto web_ctx = webkit_web_context_get_default();
    auto module_path = g_build_filename(g_get_current_dir(),
                                        "modules/",
                                        NULL);

    std::cout << "MODULE LOAD PATH: " << module_path << "\n";
    webkit_web_context_set_web_extensions_directory(web_ctx, module_path);

    WebKitSettings *settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));

    webkit_settings_set_enable_webgl(settings, true);
    webkit_settings_set_enable_developer_extras(settings, true);
    g_object_set(settings, "enable-javascript", TRUE, NULL);

    string url;

    if (debug != 'D')
        url = string("file://") + current_path().string() + string("/ui/ressources/index.html");
    else
        url = "http://127.0.0.1:3000";

    std::cout << url << std::endl;
    webkit_web_view_load_uri(webview, url.c_str());
    this->set_size_request(800, 600);

    this->show_all();
}