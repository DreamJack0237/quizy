#include "ui/Webview.h"
using std::string;

int main(int argc, char *argv[])
{
    // Initialize GTKmm
    Gtk::Main kit(argc, argv);
    View window("Quizy");

    Gtk::Main::run(window);
    return 0;
}