
#include <iostream>
#include <gtk/gtk.h>
#include "version.h"

GtkWidget *g_wndMain;

// Don't forget to set DISPLAY env variable
void print_usage(char *argv)
{
    std::cout << argv << " (v" << project_VERSION_MAJOR << "."
    << project_VERSION_MINOR << "."
    << project_VERSION_PATCH << ")" << std::endl;
    std::cout << "Usage: " << argv << " <TBD>" << std::endl;
}
void echo_input_args(int argc, char **argv)
{
    std::cout << "Input Arguments:" << std::endl;
    for (int i = 0; i < argc; i++)
    {
        std::cout << "\targv[" << i << "] = " << argv[i] << std::endl;
    }
}

extern "C" void closeButtonClicked(__attribute__((unused)) GtkWidget *btnSrc,
                              __attribute__((unused)) gpointer *user_date)
{
    if (g_wndMain != gtk_widget_get_toplevel(btnSrc)){
        gtk_window_close(GTK_WINDOW(gtk_widget_get_toplevel(btnSrc)));
    } else {
        gtk_main_quit();
    }
}

extern "C" gboolean windowDelete(__attribute__((unused)) GtkWidget *eventSrc,
                      __attribute__((unused)) GdkEvent *event,
                      __attribute__((unused)) gpointer data)
{
    if (g_wndMain == gtk_widget_get_toplevel(eventSrc)) {
        gtk_main_quit();
    }
    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further (though it doesn't seem to quit the main thread unless we explicitly
    // call gtk_main_quit();
    return FALSE;
}

extern "C" void testBtnClicked(__attribute__((unused)) GtkWidget *btnSrc,
                           __attribute__((unused)) gpointer *user_date)
{
    static int test_count = 1;
    static bool first = true;
    if (first) {
        g_print("Testing... testing %d...\n", test_count);
        first = false;
    } else {
        g_print("%d...\n", test_count);
    }
    test_count++;
}

extern "C" void openChildGladeWnd(__attribute__((unused)) GtkWidget *parent,
                       __attribute__((unused)) gpointer *endowment)
{
    GtkWidget *ref_wndGladeMain;
    GtkBuilder *guiBuilder;

    guiBuilder = gtk_builder_new();

    if (gtk_builder_add_from_file(guiBuilder, "wndGladeMain.glade", nullptr) == 0)
    {
        g_print("%s: failed to load %s", __func__ , "wndGladeMain.glade");
    }
    ref_wndGladeMain = GTK_WIDGET(gtk_builder_get_object(guiBuilder, "wndGladeMain"));
    gtk_builder_connect_signals(guiBuilder, nullptr);
    gtk_widget_show_all(ref_wndGladeMain);
    g_object_unref(guiBuilder);
}

extern "C" void launchChildWnd(__attribute__((unused)) GtkWidget *btnSrc,
                           __attribute__((unused)) gpointer *user_date)
{
    openChildGladeWnd(gtk_widget_get_toplevel(btnSrc), user_date);
}

extern "C" void loadWndMainContent(GtkWidget *parentWnd)
{
    GtkWidget *btnBox;
    GtkWidget *btnClose;
    GtkWidget *btnTest;

    btnBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

    btnClose = gtk_button_new_with_label("Close");
    btnTest = gtk_button_new_with_label("Test");
    gtk_container_add(GTK_CONTAINER (btnBox), btnTest);
    gtk_container_add(GTK_CONTAINER (btnBox), btnClose);
    gtk_container_add(GTK_CONTAINER (parentWnd), btnBox);

    g_signal_connect(btnTest, "clicked", G_CALLBACK(launchChildWnd), NULL);
    g_signal_connect(btnClose, "clicked", G_CALLBACK(closeButtonClicked), NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    } else {
        // just because I don't know what else to do with them now and like leaving dev
        // hooks in sandboxes.
        echo_input_args(argc, argv);
    }

    GtkWidget *wndMain;
    gtk_init(&argc , &argv);

    wndMain = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_wndMain = wndMain;
    g_signal_connect(wndMain, "delete-event", G_CALLBACK(windowDelete), NULL);

    loadWndMainContent(wndMain);

    gtk_widget_show_all(wndMain);
    gtk_main();

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
