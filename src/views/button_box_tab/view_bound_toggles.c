/*
 * Created by french on 3/2/24.
*/
#include <gtk/gtk.h>
#include "globals.h"
#include "view_bound_toggles.h"
#include "views/root/view_msgout.h"
#include "utils/logging.h"

void on_tbBindingSrc_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: binding source is <%s>\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "active":"inactive");
}

void on_tbBiDirModelBoundEnable_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: Model Bound Toggle %s\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "Enabled":"Disabled");
}

void on_bPrintModelEnableState_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: modelDeviceA is %s\n",
                   __func__,
                   model_device_get_enabled(modelDeviceA) ? "enabled":"disabled");
}

void on_bUnboundModelEnable_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: enabling model\n", __func__);
   model_device_set_enabled(modelDeviceA, TRUE);
}

void on_bUnboundModelDisable_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: enabling model\n", __func__);
   model_device_set_enabled(modelDeviceA, FALSE);
}

static gboolean placeholder_loaded = TRUE;
static char widget_default_title[] = "Placeholder Widget";


void on_btn_faux_dlg_load_widget_clicked(GtkButton *button, AppWidgets_T *app_wdgts)
{
   GtkBuilder      *dlg_builder;
//    app_widgets     *content_widgets = g_slice_new(app_wdgts);

   GtkWidget *parent = gtk_widget_get_parent(app_wdgts->w_faux_dlg_content);

   if (placeholder_loaded){
      gtk_header_bar_set_title(GTK_HEADER_BAR(app_wdgts->w_hdrbr_faux_dlg), "Sample Widget Loaded");
      gtk_button_set_label (button, "Load Placeholder");
      placeholder_loaded = FALSE;

      gtk_container_remove(GTK_CONTAINER(parent), app_wdgts->w_faux_dlg_content);

      dlg_builder = gtk_builder_new_from_resource("/sandbox/resources/dlg_sample_a.glade");
      app_wdgts->w_faux_dlg_content = GTK_WIDGET(gtk_builder_get_object(dlg_builder, "grd_child_layout_standalone"));
      app_wdgts->w_btn_draw_dsa_drawing_area_red = GTK_WIDGET(gtk_builder_get_object(dlg_builder, "btn_draw_dsa_drawing_area_red"));
      app_wdgts->w_btn_draw_dsa_drawing_area_blue = GTK_WIDGET(gtk_builder_get_object(dlg_builder, "btn_draw_dsa_drawing_area_blue"));
      app_wdgts->w_dsa_drawing_area = GTK_WIDGET(gtk_builder_get_object(dlg_builder, "dsa_drawing_area"));
   } else {
      gtk_header_bar_set_title(GTK_HEADER_BAR(app_wdgts->w_hdrbr_faux_dlg), widget_default_title);
      gtk_button_set_label (button, "Load Sample");
      placeholder_loaded = FALSE;

      gtk_container_remove(GTK_CONTAINER(parent), app_wdgts->w_btn_draw_dsa_drawing_area_red);
      gtk_container_remove(GTK_CONTAINER(parent), app_wdgts->w_btn_draw_dsa_drawing_area_blue);
      gtk_container_remove(GTK_CONTAINER(parent), app_wdgts->w_dsa_drawing_area);
      gtk_container_remove(GTK_CONTAINER(parent), app_wdgts->w_faux_dlg_content);

      dlg_builder = gtk_builder_new_from_resource("/sandbox/resources/dlg_sample_b.glade");
      app_wdgts->w_faux_dlg_content = GTK_WIDGET(gtk_builder_get_object(dlg_builder, "grd_child_placeholder_standalone"));
   }

   gtk_box_pack_start (GTK_BOX(parent), app_wdgts->w_faux_dlg_content, TRUE, TRUE, 0);
   gtk_box_reorder_child(GTK_BOX(parent), app_wdgts->w_faux_dlg_content, 0);

   gtk_builder_connect_signals(dlg_builder, app_wdgts);

//   GSList *list = gtk_builder_get_objects(dlg_builder);
//   g_slist_foreach(list, genericWidgetSetup, app_wdgts->w_faux_dlg_content);
//   g_slist_free(list);

   g_object_unref(dlg_builder);
   gtk_widget_queue_resize(parent);
   gtk_widget_show_all(parent);
}

void on_pod_dev_test_bnt_clicked(GtkButton *button, GtkDialog *dialog)
{
   (void) button;
   // Set up dialog to be transient from main window
   gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(g_appWidgetsT->w_mainAppWnd));
   gtk_widget_show(GTK_WIDGET(dialog));
}
