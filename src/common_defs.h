/*
 * Created by french on 2/18/24.
*/
#ifndef GTKSANDBOX_COMMON_DEFS_H
#define GTKSANDBOX_COMMON_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif
#include <gtk/gtk.h>

#define REALLY_LONG_ISO_TIME_STRING "2000-01-31T12:34:56.789-01:23"

typedef enum {
   SUCCESS,
   PARSE_ARG_ERR,
   DISPLAY_ENV_ERR // TODO: fill in more values here... or delete this
} RVALUE_T;

typedef enum {
   LOGLEVEL_DEBUG,
   LOGLEVEL_INFO,
   LOGLEVEL_ERROR
} LOGLEVEL_T;

extern const char* DEBUG_STR;
extern const char* INFO_STR;
extern const char* ERROR_STR;
extern const int   LOGGING_MAX_MSG_LENGTH;

typedef struct {
   // ********************************************************************************
   // Basic app framework
   GtkWidget   *w_mainAppWnd;
   GtkWidget   *w_tvAppMsgOut;
   GtkWidget   *w_btnCloseMainApp;

   // ********************************************************************************
   GtkWidget   *w_nbExamplesTabs;
   GtkWidget   *w_nblblSamplesTab;
   GtkWidget   *w_nbSamplesTab;
   GtkWidget   *w_nblblBottonBoxTab;
   GtkWidget   *w_nbButtonBoxTab;
   GtkWidget   *w_nblblMiscTab;
   GtkWidget   *w_nbMiscTab;
   GtkWidget   *w_nblblWizardTab;
   GtkWidget   *w_nbWizardTab;

   // ********************************************************************************
   // Button binding example
   GtkWidget   *w_tbBindingSrc;
   GtkWidget   *w_tbBoundTarget1;
   GtkWidget   *w_tbBoundTarget2;
   // Button toggle example
   GtkWidget   *w_tbTextSwapToggleExample;
   // Custom model, two-way bound toggle, with model toggles and print of model state
   GtkWidget   *w_tbBiDirModelBoundEnable;
   GtkWidget   *w_bUnboundModelEnable;
   GtkWidget   *w_bUnboundModelDisable;
   GtkWidget   *w_bPrintModelEnableState;

   // ********************************************************************************
   // Child wnd launching example
   GtkWidget   *w_btnLaunchChildWnd;
   GtkWidget   *w_lblChildCount;
   GtkWidget   *w_tvChildMsgOutViewer;

   GtkWidget   *w_content_area;
   GtkWidget   *w_main_setup_slide_stack;
   GtkWidget   *w_setup_start_page;

   // ********************************************************************************
   // Samples table example using a TreeView, row selection, row view and row manipulation
   // Tree Selection is NOT a widget, but is essentially bound to the tree view
   GtkWidget   *w_trvwSamplesTable;
   GObject     *g_trslctnSelectedSample;

   GtkWidget   *w_tbtnEditSelection;
   GtkWidget   *w_tbtnCreateRow;
   GtkWidget   *w_tbtnDeleteRow;
   GtkWidget   *w_ppvrAreYouSure;
   GtkWidget   *w_lblPopoverAreYouSureMsg;
   GtkWidget   *w_btnAreYouSureConfirm;
   GtkWidget   *w_btnAreYouSureCancel;

   GtkWidget   *w_editSampleDateTime;
   GtkWidget   *w_lblSampleDate;
   GtkWidget   *w_entrySampleHour;
   GtkWidget   *w_entrySampleMinute;
   // Popover Datepicker
   GtkWidget   *w_ppvrDatepicker;
   GtkWidget   *w_popCalendar;
   GtkWidget   *w_popDone;
   GtkWidget   *w_popCancel;

   GtkWidget   *w_entryMeasurement1;
   GtkWidget   *w_entryMeasurement2;
   GtkWidget   *w_entryMeasurement3;
   GtkWidget   *w_entryMeasurement4;

   GtkWidget   *w_entryCalculationA;
   GtkWidget   *w_entryCalculationB;

   GtkWidget   *w_btnChangeRow;
   GtkWidget   *w_btnCancelRowChange;

   // ********************************************************************************
   GtkWidget   *w_stck_SetupWizard;
   GtkWidget   *w_stckpg_HorizontalPair;
   GtkWidget   *w_btn_HorizontalPair_next;
   GtkWidget   *w_btn_HorizontalPair_back;
   GtkWidget   *w_stckpg_GridPage;
   GtkWidget   *w_btn_GridPage_next;
   GtkWidget   *w_btn_GridPage_back;
   GtkWidget   *w_stckpg_VerticalPair;
   GtkWidget   *w_btn_VerticalPair_next;
   GtkWidget   *w_btn_VerticalPair_back;
   GtkWidget   *w_stckpg_HorizontalPair1;
   GtkWidget   *w_btn_HorizontalPair_next1;
   GtkWidget   *w_btn_HorizontalPair_back1;

} AppWidgets_T;


#ifdef __cplusplus
}  /* closing brace for extern "C" */
#endif
#endif  /* GTKSANDBOX_COMMON_DEFS_H */
