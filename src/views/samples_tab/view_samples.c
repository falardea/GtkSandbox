/*
 * Created by french on 3/6/24.
*/
#include "view_samples.h"
#include "../../models/model_samples.h"
#include "../../utils/logging.h"

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
