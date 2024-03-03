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
   DISPLAY_ENV_ERR
} RVALUE_T;

typedef struct {
   GtkWidget *w_mainAppWnd;
   GtkWidget *w_btnCloseMainApp;

   GtkWidget *w_tbBindingSrc;
   GtkWidget *w_tbBoundTarget1;
   GtkWidget *w_tbBoundTarget2;
   GtkWidget *w_tbModelToggle;

   GtkWidget *w_btnLaunchChildWnd;
} AppWidgets_T;

#ifdef __cplusplus
}  /* closing brace for extern "C" */
#endif
#endif  /* GTKSANDBOX_COMMON_DEFS_H */
