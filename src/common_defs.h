/*
 * Created by french on 2/18/24.
*/
#ifndef GTKSANDBOX_COMMON_DEFS_H
#define GTKSANDBOX_COMMON_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif
#include <gtk/gtk.h>

typedef enum {
   SUCCESS,
   PARSE_ARG_ERR,
   DISPLAY_ENV_ERR // TODO: fill in more values here... or delete this
} RVALUE_T;

typedef struct {
   GtkWidget *w_mainAppWnd;
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
   GtkWidget *w_btnPrintSelection;


   GObject *g_trslctnSelectedSample;

} AppWidgets_T;


#ifdef __cplusplus
}  /* closing brace for extern "C" */
#endif
#endif  /* GTKSANDBOX_COMMON_DEFS_H */
