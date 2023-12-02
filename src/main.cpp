#include <iostream>
#include <gtk/gtk.h>
#include "version.h"

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

static void closeButtonClicked(__attribute__((unused)) GtkWidget *btnSrc,
                              __attribute__((unused)) gpointer *user_date)
{
    g_print("%s called\n", __func__ );
    gtk_main_quit();
}

gboolean windowDelete(__attribute__((unused)) GtkWidget *eventSrc,
                      __attribute__((unused)) GdkEvent *event,
                      __attribute__((unused)) gpointer data)
{
    g_print("%s called\n", __func__);
    // TRUE to stop other handlers from being invoked for the event.
    // FALSE to propagate the event further*
    gtk_main_quit();
    return TRUE;
    // * returning False is "supposed" to let downstream event handlers
    // fire and handle the destroy event, but doesn't appear to on my
    // home system
}

static void testBtnClicked(__attribute__((unused)) GtkWidget *btnSrc,
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

void loadWndMainContent(GtkWidget *parentWnd)
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

    g_signal_connect(btnTest, "clicked", G_CALLBACK(testBtnClicked), NULL);
    g_signal_connect(btnClose, "clicked", G_CALLBACK(closeButtonClicked), NULL);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    } else {
        echo_input_args(argc, argv);
    }

    GtkWidget *wndMain;
    gtk_init(&argc , &argv);

    wndMain = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(wndMain, "delete-event", G_CALLBACK(windowDelete), NULL);

    loadWndMainContent(wndMain);

    gtk_widget_show_all(wndMain);
    gtk_main();

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
