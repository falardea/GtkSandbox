/*
 * Created by french on 3/6/24.
*/
#include "view_samples.h"
#include "../../models/model_samples.h"
#include "../../utils/logging.h"
#include "common_defs.h"

void build_samples_view(GtkWidget *samplesTable)
{
   GtkCellRenderer *cellRenderer;

   cellRenderer = gtk_cell_renderer_text_new();
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "Timestamp",
                                               cellRenderer, "text", COL_TIMESTAMP, NULL);

   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "Meas1",
                                               cellRenderer, "text", COL_MEASUREMENT_1, NULL);
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "Meas2",
                                               cellRenderer, "text", COL_MEASUREMENT_2, NULL);
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "Meas3",
                                               cellRenderer, "text", COL_MEASUREMENT_3, NULL);
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "Meas4",
                                               cellRenderer, "text", COL_MEASUREMENT_4, NULL);

   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "CalcA",
                                               cellRenderer, "text", COL_CALCULATED_A, NULL);
   gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(samplesTable), -1, "CalcB",
                                               cellRenderer, "text", COL_CALCULATED_B, NULL);
   logging_llprint(LOGLEVEL_DEBUG, "%s\n", __func__);
}

void on_btnPrintSelection_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   GtkTreeModel *samplesModel;

   /* If there is a selection, this button should only be enabled if there is a selection */
   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(appWidgetsT->g_trslctnSelectedSample),
                                        &samplesModel,
                                        &tableCursor))
   {
      /* Get the selection */
      /* tableCursor is set if there is a selection */
      char testMsg[256];
      snprintf(testMsg, sizeof (testMsg), "%s:  +++  +++  Test Message +++ +++\n", __func__);
      logging_llprint(LOGLEVEL_DEBUG, "%s", testMsg);
      gtk_label_set_label(GTK_LABEL(appWidgetsT->w_lblSelectionText), testMsg);
   }
}


void on_sample_selection_changed(GtkTreeSelection* self,
                                 gpointer user_data)
{
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   gboolean enableEdit = FALSE;

   /* If there is a selection, this button should only be enabled if there is a selection */
   logging_llprint(LOGLEVEL_DEBUG, "%s\n", __func__);
   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(self),
                                        NULL,
                                        &tableCursor))
   {
      enableEdit = TRUE;
   }
   gtk_widget_set_sensitive(GTK_WIDGET(appWidgetsT->w_btnPrintSelection), enableEdit);
}
