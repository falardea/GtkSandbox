//
// Created by french on 2/3/24.
//

#include "app_view.h"

void on_btnCloseMainApp_clicked(__attribute__((unused)) GtkWidget *srcWidget,
                                __attribute__((unused)) gpointer uData)
{
    g_print("%s called\n", __func__);
    gtk_main_quit();
}

gboolean on_mainAppWnd_delete_event(__attribute__((unused)) GtkWidget *srcWidget,
                                    __attribute__((unused)) GdkEvent *event,
                                    __attribute__((unused)) gpointer uData)
{
    g_print("%s called\n", __func__);
    gtk_main_quit();
    return FALSE;
}