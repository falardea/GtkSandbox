//
// Created by french on 2/3/24.
//

#include "view_app_root.h"
#include "views/misc_tab/view_app_child.h"

void on_btnCloseMainApp_clicked(__attribute__((unused)) GtkWidget *srcWidget,
                                __attribute__((unused)) gpointer uData) {
   gtk_main_quit();
}

gboolean on_mainAppWnd_delete_event(__attribute__((unused)) GtkWidget *srcWidget,
                                    __attribute__((unused)) GdkEvent *event,
                                    __attribute__((unused)) gpointer uData) {
   gtk_main_quit();
   return FALSE;
}

