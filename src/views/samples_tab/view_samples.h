/*
 * Created by french on 3/6/24.
*/
#ifndef GTKSANDBOX_VIEW_SAMPLES_H
#define GTKSANDBOX_VIEW_SAMPLES_H
#include <gtk/gtk.h>
#include "globals.h"

void build_samples_view(GtkWidget *samplesTable);
void on_btnPrintSelection_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data);

#endif  /* GTKSANDBOX_VIEW_SAMPLES_H */
