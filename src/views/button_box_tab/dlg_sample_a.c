/*
 * Copyright (c) 2023 Deka Research and Development. All rights reserved.
 * Created by rfalardeau on 10/2/2023. 
 */

#include <gtk/gtk.h>
#include "dlg_sample_a.h"

void btn_draw_dsa_drawing_area_red(GtkButton *button, AppWidgets_T *app_wdgts){
    (void) button;
    GtkStyleContext *dlgContext;
    dlgContext = gtk_widget_get_style_context(gtk_widget_get_parent(app_wdgts->w_dsa_drawing_area));
    gtk_style_context_add_class(dlgContext, "faux_dlg_child_empty_red");
    gtk_style_context_remove_class(dlgContext, "faux_dlg_child_empty_blue");
}

void btn_draw_dsa_drawing_area_blue(GtkButton *button, AppWidgets_T *app_wdgts){
    (void) button;
    GtkStyleContext *dlgContext;
    dlgContext = gtk_widget_get_style_context(gtk_widget_get_parent(app_wdgts->w_dsa_drawing_area));
    gtk_style_context_add_class(dlgContext, "faux_dlg_child_empty_blue");
    gtk_style_context_remove_class(dlgContext, "faux_dlg_child_empty_red");
}
