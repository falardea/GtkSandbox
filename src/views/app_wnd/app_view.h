//
// Created by french on 2/3/24.
//

#ifndef SANDBOX_APP_VIEW_H
#define SANDBOX_APP_VIEW_H
#include <gtk/gtk.h>

void on_btnCloseMainApp_clicked(__attribute__((unused)) GtkWidget *srcWidget,
                                __attribute__((unused)) gpointer uData);

gboolean on_mainAppWnd_delete_event(__attribute__((unused)) GtkWidget *srcWidget,
                                    __attribute__((unused)) GdkEvent *event,
                                    __attribute__((unused)) gpointer uData);

#endif //SANDBOX_APP_VIEW_H
