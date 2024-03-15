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
   GtkWidget *w_mainAppWnd;
   GtkWidget *w_tvAppMsgOut;
   GtkWidget *w_btnCloseMainApp;

   GtkWidget *w_tbBindingSrc;
   GtkWidget *w_tbBoundTarget1;
   GtkWidget *w_tbBoundTarget2;
   GtkWidget *w_tbTextSwapToggleExample;

   GtkWidget *w_tbBiDirModelBoundEnable;
   GtkWidget *w_bUnboundModelEnable;
   GtkWidget *w_bUnboundModelDisable;
   GtkWidget *w_bPrintModelEnableState;

   GtkWidget *w_btnLaunchChildWnd;
   GtkWidget *w_lblChildCount;

   GtkWidget *w_tvChildMsgOutViewer;

   GtkWidget *w_trvwSamplesTable;
   GtkWidget *w_lblSelectionText;
   GtkWidget *w_btnEditSelection;
   GtkWidget *w_btnCreateRow;
   GtkWidget *w_btnDeleteRow;
   GtkWidget *w_btnChangeRow;
   GtkWidget *w_btnCancelRowChange;
   GtkWidget *w_editSampleDateTime;
   GtkWidget *w_lblSampleDate;
   GtkWidget *w_entrySampleHour;
   GtkWidget *w_entrySampleMinute;
   GtkWidget *w_entryMeasurement1;
   GtkWidget *w_entryMeasurement2;
   GtkWidget *w_entryMeasurement3;
   GtkWidget *w_entryMeasurement4;
   GtkWidget *w_entryCalculationA;
   GtkWidget *w_entryCalculationB;

   // Popover Datepicker
   GtkWidget *w_ppvrDatepicker;
   GtkWidget *w_popCalendar;
   GtkWidget *w_popDone;
   GtkWidget *w_popCancel;

   // Popover Confirm/Cancel
   GtkWidget *w_ppvrAreYouSure;
   GtkWidget *w_lblPopoverAreYouSureMsg;
   GtkWidget *w_btnAreYouSureConfirm;
   GtkWidget *w_btnAreYouSureCancel;

   GObject *g_trslctnSelectedSample;

} AppWidgets_T;


#ifdef __cplusplus
}  /* closing brace for extern "C" */
#endif
#endif  /* GTKSANDBOX_COMMON_DEFS_H */
