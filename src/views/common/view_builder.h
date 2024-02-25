//
// Created by french on 2/3/24.
//

#ifndef SANDBOX_VIEW_BUILDER_H
#define SANDBOX_VIEW_BUILDER_H

#include <gtk/gtk.h>

typedef struct {
   GtkWidget *w_mainAppWnd;
   GtkWidget *w_btnCloseMainApp;

   GtkWidget *w_tbBindingSrc;
   GtkWidget *w_tbBoundTarget1;
   GtkWidget *w_tbBoundTarget2;

   GtkWidget *w_btnLaunchChildWnd;
} AppWidgets_T;

AppWidgets_T *build_application(void);

#endif  // SANDBOX_VIEW_BUILDER_H
