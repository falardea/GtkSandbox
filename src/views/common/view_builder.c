//
// Created by french on 2/3/24.
//
#include <gtk/gtk.h>
#include "view_builder.h"

#define POSSIBLE_TOGGLE_TEXT_LENGTH 2

gboolean activeTBTextSwap(GBinding *src, const GValue *fromValue, GValue *toValue, gpointer user_data)
{
    GtkToggleButton *tbutton = (GtkToggleButton *)g_binding_dup_source(src);
    if (tbutton != NULL)
    {
        gboolean active = g_value_get_boolean(fromValue);
        gtk_button_set_label(GTK_BUTTON(tbutton), active ? "ON" : "OFF");
        return TRUE;
    }
    return FALSE;
}

AppWidgets_T *build_application(void)
{
    GtkBuilder *builder;

    AppWidgets_T *appWidgetsT = g_slice_new(AppWidgets_T);

    builder = gtk_builder_new();

    if(gtk_builder_add_from_file(builder, "sandbox.glade", NULL) == 0)
    {
        printf("gtk_builder_add_from_file failed to load glade resource\n");
        return NULL;
    }

    appWidgetsT->w_mainAppWnd = GTK_WIDGET(gtk_builder_get_object(builder, "app_wnd"));
    appWidgetsT->w_btnCloseMainApp = GTK_WIDGET(gtk_builder_get_object(builder, "btnCloseMainApp"));
    appWidgetsT->w_tbBindingSrc = GTK_WIDGET(gtk_builder_get_object(builder, "tbBindingSrc"));
    appWidgetsT->w_tbBoundTarget1 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget1"));
    appWidgetsT->w_tbBoundTarget2 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget2"));

    gtk_builder_connect_signals(builder, appWidgetsT);

    g_object_bind_property(appWidgetsT->w_tbBindingSrc, "active",
                           appWidgetsT->w_tbBoundTarget1, "sensitive",
                           G_BINDING_DEFAULT);
    g_object_bind_property(appWidgetsT->w_tbBindingSrc, "active",
                           appWidgetsT->w_tbBoundTarget2, "sensitive",
                           G_BINDING_DEFAULT);
    g_object_bind_property_full(appWidgetsT->w_tbBindingSrc, "active",
                                appWidgetsT->w_tbBindingSrc, "label",
                                G_BINDING_SYNC_CREATE,
                                (GBindingTransformFunc) activeTBTextSwap,
                                NULL,
                                NULL, NULL);

    g_object_unref(builder);
    return appWidgetsT;
}
