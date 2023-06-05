#include <gtkmm.h>
#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>
#include <iostream>
#include <filesystem>
#include <fstream>
using std::string;
using std::filesystem::current_path;
class View : public Gtk::Window
{
private:
    WebKitWebView *webview;

public:
    View(string title);
};