/*
 * Created by french on 3/2/24.
*/
#ifndef GTKSANDBOX_VIEW_BOUND_TOGGLES_H
#define GTKSANDBOX_VIEW_BOUND_TOGGLES_H
#include <gtk/gtk.h>

void on_tbBindingSrc_toggled(GtkToggleButton *tbutton, gpointer *user_data);
void on_tbBiDirModelBoundEnable_toggled(GtkToggleButton *tbutton, gpointer *user_data);
void on_bPrintModelEnableState_clicked(GtkButton *button, gpointer *user_data);
void on_bUnboundModelEnable_clicked(GtkButton *button, gpointer *user_data);
void on_bUnboundModelDisable_clicked(GtkButton *button, gpointer *user_data);

#endif  /* GTKSANDBOX_VIEW_BOUND_TOGGLES_H */
