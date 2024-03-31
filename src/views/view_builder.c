//
// Created by french on 2/3/24.
//
#include <gtk/gtk.h>
#include "globals.h"
#include "view_builder.h"
#include "utils/logging.h"
#include "models/model_samples.h"
#include "views/samples_tab/view_samples.h"

gboolean transform_toggle_label_on_off(GBinding *src, const GValue *fromValue,  __attribute__((unused)) GValue *toValue,
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
   g_object_bind_property_full(tbutton, "active",
                               tbutton, "label",
                               G_BINDING_SYNC_CREATE,
                               (GBindingTransformFunc) transform_toggle_label_on_off,
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

   if (gtk_builder_add_from_resource(builder, "/sandbox/resources/sandbox.glade", NULL) == 0) {
      logging_llprintf(LOGLEVEL_ERROR, "gtk_builder_add_from_file failed to load glade resource\n");
      return NULL;
   }

   // ********************************************************************************
   // Map the objects we've described in the glade file to our widget references
   // ********************************************************************************
   appWidgetsT->w_mainAppWnd = GTK_WIDGET(gtk_builder_get_object(builder, "app_wnd"));
   appWidgetsT->w_btnCloseMainApp = GTK_WIDGET(gtk_builder_get_object(builder, "btnCloseMainApp"));
   appWidgetsT->w_tvAppMsgOut = GTK_WIDGET(gtk_builder_get_object(builder, "tvAppMsgOut"));

   // ********************************************************************************
   appWidgetsT->w_nbExamplesTabs = GTK_WIDGET(gtk_builder_get_object(builder, "nbExamplesTabs"));
   appWidgetsT->w_nblblSamplesTab = GTK_WIDGET(gtk_builder_get_object(builder, "nblblSamplesTab"));
   appWidgetsT->w_nbSamplesTab = GTK_WIDGET(gtk_builder_get_object(builder, "nbSamplesTab"));
   appWidgetsT->w_nblblBottonBoxTab = GTK_WIDGET(gtk_builder_get_object(builder, "nblblBottonBoxTab"));
   appWidgetsT->w_nbButtonBoxTab = GTK_WIDGET(gtk_builder_get_object(builder, "nbButtonBoxTab"));
   appWidgetsT->w_nblblMiscTab = GTK_WIDGET(gtk_builder_get_object(builder, "nblblMiscTab"));
   appWidgetsT->w_nbMiscTab = GTK_WIDGET(gtk_builder_get_object(builder, "nbMiscTab"));
   appWidgetsT->w_nblblWizardTab = GTK_WIDGET(gtk_builder_get_object(builder, "nblblWizardTab"));
   appWidgetsT->w_nbWizardTab = GTK_WIDGET(gtk_builder_get_object(builder, "nbWizardTab"));

   // ********************************************************************************
   appWidgetsT->w_tbBindingSrc = GTK_WIDGET(gtk_builder_get_object(builder, "tbBindingSrc"));
   appWidgetsT->w_tbBoundTarget1 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget1"));
   appWidgetsT->w_tbBoundTarget2 = GTK_WIDGET(gtk_builder_get_object(builder, "tbBoundTarget2"));
   appWidgetsT->w_tbTextSwapToggleExample = GTK_WIDGET(gtk_builder_get_object(builder, "tbTextSwapToggleExample"));
   appWidgetsT->w_tbBiDirModelBoundEnable = GTK_WIDGET(gtk_builder_get_object(builder, "tbBiDirModelBoundEnable"));
   appWidgetsT->w_bUnboundModelEnable = GTK_WIDGET(gtk_builder_get_object(builder, "bUnboundModelEnable"));
   appWidgetsT->w_bUnboundModelDisable = GTK_WIDGET(gtk_builder_get_object(builder, "bUnboundModelDisable"));
   appWidgetsT->w_bPrintModelEnableState = GTK_WIDGET(gtk_builder_get_object(builder, "bPrintModelEnableState"));

   // ********************************************************************************
   appWidgetsT->w_btnLaunchChildWnd = GTK_WIDGET(gtk_builder_get_object(builder, "btnLaunchChildWnd"));
   appWidgetsT->w_lblChildCount = GTK_WIDGET(gtk_builder_get_object(builder, "lblChildCount"));
   appWidgetsT->w_tvChildMsgOutViewer = GTK_WIDGET(gtk_builder_get_object(builder, "tvChildMsgOutViewer"));

   // ********************************************************************************
   appWidgetsT->w_trvwSamplesTable = GTK_WIDGET(gtk_builder_get_object(builder, "trvwSamplesTable"));
   appWidgetsT->g_trslctnSelectedSample = G_OBJECT(gtk_builder_get_object(builder, "trslctnSelectedSample"));

   appWidgetsT->w_tbtnEditSelection = GTK_WIDGET(gtk_builder_get_object(builder, "tbtnEditSelection"));
   appWidgetsT->w_tbtnCreateRow = GTK_WIDGET(gtk_builder_get_object(builder, "tbtnCreateRow"));
   appWidgetsT->w_tbtnDeleteRow = GTK_WIDGET(gtk_builder_get_object(builder, "tbtnDeleteRow"));
   appWidgetsT->w_ppvrAreYouSure = GTK_WIDGET(gtk_builder_get_object(builder, "ppvrAreYouSure"));
   appWidgetsT->w_lblPopoverAreYouSureMsg = GTK_WIDGET(gtk_builder_get_object(builder, "lblPopoverAreYouSureMsg"));
   appWidgetsT->w_btnAreYouSureConfirm = GTK_WIDGET(gtk_builder_get_object(builder, "btnAreYouSureConfirm"));
   appWidgetsT->w_btnAreYouSureCancel = GTK_WIDGET(gtk_builder_get_object(builder, "btnAreYouSureCancel"));

   appWidgetsT->w_editSampleDateTime = GTK_WIDGET(gtk_builder_get_object(builder, "editSampleDateTime"));
   appWidgetsT->w_lblSampleDate = GTK_WIDGET(gtk_builder_get_object(builder, "lblSampleDate"));
   appWidgetsT->w_entrySampleHour = GTK_WIDGET(gtk_builder_get_object(builder, "entrySampleHour"));
   appWidgetsT->w_entrySampleMinute = GTK_WIDGET(gtk_builder_get_object(builder, "entrySampleMinute"));
   // Datepicker
   appWidgetsT->w_ppvrDatepicker = GTK_WIDGET(gtk_builder_get_object(builder, "ppvrDatepicker"));
   appWidgetsT->w_popCalendar = GTK_WIDGET(gtk_builder_get_object(builder, "popCalendar"));
   appWidgetsT->w_popDone = GTK_WIDGET(gtk_builder_get_object(builder, "popDone"));
   appWidgetsT->w_popCancel = GTK_WIDGET(gtk_builder_get_object(builder, "popCancel"));

   appWidgetsT->w_entryMeasurement1 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement1"));
   appWidgetsT->w_entryMeasurement2 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement2"));
   appWidgetsT->w_entryMeasurement3 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement3"));
   appWidgetsT->w_entryMeasurement4 = GTK_WIDGET(gtk_builder_get_object(builder, "entryMeasurement4"));

   appWidgetsT->w_entryCalculationA = GTK_WIDGET(gtk_builder_get_object(builder, "entryCalculationA"));
   appWidgetsT->w_entryCalculationB = GTK_WIDGET(gtk_builder_get_object(builder, "entryCalculationB"));

   appWidgetsT->w_btnChangeRow = GTK_WIDGET(gtk_builder_get_object(builder, "btnChangeRow"));
   appWidgetsT->w_btnCancelRowChange = GTK_WIDGET(gtk_builder_get_object(builder, "btnCancelRowChange"));

   // set up the table column definitions
   build_samples_view(appWidgetsT->w_trvwSamplesTable);
   // build, and possibly populate from <...>, a model of the data to bind to the table as its "TreeModel"
   gtk_tree_view_set_model(GTK_TREE_VIEW(appWidgetsT->w_trvwSamplesTable), build_samples_model());


   // ********************************************************************************
   appWidgetsT->w_stck_SetupWizard = GTK_WIDGET(gtk_builder_get_object(builder, "stck_SetupWizard"));
   appWidgetsT->w_stckpg_HorizontalPair = GTK_WIDGET(gtk_builder_get_object(builder, "stckpg_HorizontalPair"));
   appWidgetsT->w_btn_HorizontalPair_next = GTK_WIDGET(gtk_builder_get_object(builder, "btn_HorizontalPair_next"));
   appWidgetsT->w_btn_HorizontalPair_back = GTK_WIDGET(gtk_builder_get_object(builder, "btn_HorizontalPair_back"));
   appWidgetsT->w_stckpg_GridPage = GTK_WIDGET(gtk_builder_get_object(builder, "stckpg_GridPage"));
   appWidgetsT->w_btn_GridPage_next = GTK_WIDGET(gtk_builder_get_object(builder, "btn_GridPage_next"));
   appWidgetsT->w_btn_GridPage_back = GTK_WIDGET(gtk_builder_get_object(builder, "btn_GridPage_back"));
   appWidgetsT->w_stckpg_VerticalPair = GTK_WIDGET(gtk_builder_get_object(builder, "stckpg_VerticalPair"));
   appWidgetsT->w_btn_VerticalPair_next = GTK_WIDGET(gtk_builder_get_object(builder, "btn_VerticalPair_next"));
   appWidgetsT->w_btn_VerticalPair_back = GTK_WIDGET(gtk_builder_get_object(builder, "btn_VerticalPair_back"));
   appWidgetsT->w_stckpg_HorizontalPair1 = GTK_WIDGET(gtk_builder_get_object(builder, "stckpg_HorizontalPair1"));
   appWidgetsT->w_btn_HorizontalPair_next1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_HorizontalPair_next1"));
   appWidgetsT->w_btn_HorizontalPair_back1 = GTK_WIDGET(gtk_builder_get_object(builder, "btn_HorizontalPair_back1"));

   // ********************************************************************************
   /* appWidgetsT->w_glade_ID = GTK_WIDGET(gtk_builder_get_object(builder, "glade_ID")); */


   // ********************************************************************************
   // signals and bindings
   // ********************************************************************************
   gtk_builder_connect_signals(builder, appWidgetsT);

   bind_toggle_src_active_tar_sensitive(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbBindingSrc), appWidgetsT->w_tbBoundTarget1);
   bind_toggle_src_active_tar_sensitive(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbBindingSrc), appWidgetsT->w_tbBoundTarget2);
   bind_toggle_active_label_swap(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbTextSwapToggleExample));

   g_object_bind_property(appWidgetsT->w_tbBiDirModelBoundEnable, "active",
                          modelDeviceA, "device-enabled", G_BINDING_BIDIRECTIONAL);

   bind_toggle_src_active_tar_sensitive(GTK_TOGGLE_BUTTON(appWidgetsT->w_tbBindingSrc), appWidgetsT->w_tbBoundTarget2);

   // ********************************************************************************
   // Release anything we've instantiated with a ref-count or anything we've received allocated copies of
   // ********************************************************************************
   g_object_unref(builder);
   return appWidgetsT;
}
