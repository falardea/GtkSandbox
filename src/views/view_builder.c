//
// Created by french on 2/3/24.
//
#include <gtk/gtk.h>
#include "globals.h"
#include "view_builder.h"
#include "utils/logging.h"
#include "models/model_samples.h"
#include "views/samples_tab/view_samples.h"

gboolean transform_toggle_label_on_off(GBinding *src, const GValue *fromValue,
                                       __attribute__((unused)) GValue *toValue,
                                       __attribute__((unused)) gpointer user_data) {
   GtkToggleButton *tbutton = (GtkToggleButton *) g_binding_dup_source(src);
   if (tbutton != NULL) {
      gboolean active = g_value_get_boolean(fromValue);
      gtk_button_set_label(GTK_BUTTON(tbutton), active ? "ON" : "OFF");
      g_object_unref(tbutton);
      return TRUE;
   }
   return FALSE;
}

static void bind_toggle_active_label_swap(GtkToggleButton *tbutton)
{
   g_object_bind_property_full(tbutton, "active", tbutton, "label",
                               G_BINDING_SYNC_CREATE, (GBindingTransformFunc) transform_toggle_label_on_off,
                               NULL,NULL, NULL);
}

static void bind_toggle_src_active_tar_sensitive(GtkToggleButton *src, GtkWidget *tar)
{
   g_object_bind_property(src, "active", tar, "sensitive", G_BINDING_DEFAULT);
}

AppWidgets_T *build_application(void) {
   GtkBuilder *builder;

   AppWidgets_T *appWidgetsT = g_slice_new(AppWidgets_T);

   builder = gtk_builder_new();

   if (gtk_builder_add_from_file(builder, "sandbox.glade", NULL) == 0) {
      logging_llprintf(LOGLEVEL_ERROR, "gtk_builder_add_from_file failed to load glade resource\n");
      return NULL;
   }

   appWidgetsT->w_mainAppWnd = GTK_WIDGET(gtk_builder_get_object(builder, "app_wnd"));
   appWidgetsT->w_btnCloseMainApp = GTK_WIDGET(gtk_builder_get_object(builder, "btnCloseMainApp"));
   appWidgetsT->w_tvAppMsgOut = GTK_WIDGET(gtk_builder_get_object(builder, "tvAppMsgOut"));

   appWidgetsT->w_tbBindingSrc = GTK_WIDGET(gtk_builder_get_object(builder, "tbBindingSrc"));
   appWidgetsT->w_tbBoundTarget1 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget1"));
   appWidgetsT->w_tbBoundTarget2 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget2"));
   appWidgetsT->w_tbTextSwapToggleExample = GTK_WIDGET(gtk_builder_get_object(builder, "tbTextSwapToggleExample"));

   appWidgetsT->w_tbBiDirModelBoundEnable = GTK_WIDGET(gtk_builder_get_object(builder, "tbBiDirModelBoundEnable"));
   appWidgetsT->w_bUnboundModelEnable = GTK_WIDGET(gtk_builder_get_object(builder, "bUnboundModelEnable"));
   appWidgetsT->w_bUnboundModelDisable = GTK_WIDGET(gtk_builder_get_object(builder, "bUnboundModelDisable"));
   appWidgetsT->w_bPrintModelEnableState = GTK_WIDGET(gtk_builder_get_object(builder, "bPrintModelEnableState"));

   appWidgetsT->w_btnLaunchChildWnd = GTK_WIDGET(gtk_builder_get_object(builder, "btnLaunchChildWnd"));
   appWidgetsT->w_lblChildCount = GTK_WIDGET(gtk_builder_get_object(builder, "lblChildCount"));
   appWidgetsT->w_tvChildMsgOutViewer = GTK_WIDGET(gtk_builder_get_object(builder, "tvChildMsgOutViewer"));

   appWidgetsT->w_trvwSamplesTable = GTK_WIDGET(gtk_builder_get_object(builder, "trvwSamplesTable"));
   appWidgetsT->w_btnEditSelection = GTK_WIDGET(gtk_builder_get_object(builder, "btnEditSelection"));
   appWidgetsT->w_lblSelectionText = GTK_WIDGET(gtk_builder_get_object(builder, "lblSelectionText"));

   appWidgetsT->w_editSampleDateTime = GTK_WIDGET(gtk_builder_get_object(builder, "editSampleDateTime"));
   appWidgetsT->w_lblSampleDate = GTK_WIDGET(gtk_builder_get_object(builder, "lblSampleDate"));
   appWidgetsT->w_entrySampleHour = GTK_WIDGET(gtk_builder_get_object(builder, "entrySampleHour"));
   appWidgetsT->w_entrySampleMinute = GTK_WIDGET(gtk_builder_get_object(builder, "entrySampleMinute"));
   appWidgetsT->w_entryMeasurement1 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement1"));
   appWidgetsT->w_entryMeasurement2 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement2"));
   appWidgetsT->w_entryMeasurement3 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement3"));
   appWidgetsT->w_entryMeasurement4 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement4"));
   appWidgetsT->w_entryCalculationA = GTK_WIDGET(gtk_builder_get_object(builder, "entryCalculationA"));
   appWidgetsT->w_entryCalculationB = GTK_WIDGET(gtk_builder_get_object(builder, "entryCalculationB"));

   // Datepicker
   appWidgetsT->w_ppvrDatepicker = GTK_WIDGET(gtk_builder_get_object(builder, "ppvrDatepicker"));
   appWidgetsT->w_popCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "popCalendar"));
   appWidgetsT->w_popDone = GTK_WIDGET(gtk_builder_get_object(builder, "popDone"));
   appWidgetsT->w_popCancel = GTK_WIDGET(gtk_builder_get_object(builder, "popCancel"));

   /* appWidgetsT->w_glade_ID = GTK_WIDGET(gtk_builder_get_object(builder, "glade_ID")); */

   build_samples_view(appWidgetsT->w_trvwSamplesTable);
   gtk_tree_view_set_model(GTK_TREE_VIEW(appWidgetsT->w_trvwSamplesTable), build_samples_model());
   appWidgetsT->g_trslctnSelectedSample = G_OBJECT(gtk_builder_get_object(builder, "trslctnSelectedSample"));

   gtk_builder_connect_signals(builder, appWidgetsT);

   bind_toggle_src_active_tar_sensitive(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbBindingSrc), appWidgetsT->w_tbBoundTarget1);
   bind_toggle_src_active_tar_sensitive(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbBindingSrc), appWidgetsT->w_tbBoundTarget2);
   bind_toggle_active_label_swap(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbTextSwapToggleExample));

   g_object_bind_property(appWidgetsT->w_tbBiDirModelBoundEnable, "active",
                          modelDeviceA, "device-enabled", G_BINDING_BIDIRECTIONAL);

   g_object_unref(builder);
   return appWidgetsT;
}
