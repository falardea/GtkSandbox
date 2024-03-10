/*
 * Created by french on 3/6/24.
 *
 * Heavily influenced by the GTK 3 TreeView tutorial:
 * https://docs.gtk.org/gtk3/treeview-tutorial.html
*/
#include "model_samples.h"
#include "../utils/logging.h"

GtkListStore *sampleCalcTable;

GtkTreeModel *build_samples_model(void)

{
   sampleCalcTable = gtk_list_store_new(NUM_SAMPLES_COLUMNS,
                                               G_TYPE_STRING,
                                               G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT, G_TYPE_FLOAT,
                                               G_TYPE_DOUBLE, G_TYPE_DOUBLE);
   GtkTreeIter insertCursor;
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-01-23T12:34:56",
                      COL_MEASUREMENT_1, 1.0, COL_MEASUREMENT_2, 1.0, COL_MEASUREMENT_3, 1.0, COL_MEASUREMENT_4, 1.0,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-02-28T23:45:07",
                      COL_MEASUREMENT_1, 1.1, COL_MEASUREMENT_2, 1.2, COL_MEASUREMENT_3, 1.3, COL_MEASUREMENT_4, 1.4,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-03-04T04:56:08",
                      COL_MEASUREMENT_1, 1.2, COL_MEASUREMENT_2, 1.2, COL_MEASUREMENT_3, 1.2, COL_MEASUREMENT_4, 1.2,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-04-05T05:07:09",
                      COL_MEASUREMENT_1, 1.3, COL_MEASUREMENT_2, 1.3, COL_MEASUREMENT_3, 1.3, COL_MEASUREMENT_4, 1.3,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   gtk_list_store_append(sampleCalcTable, &insertCursor);
   gtk_list_store_set(sampleCalcTable, &insertCursor,
                      COL_TIMESTAMP, "2023-05-06T06:08:10",
                      COL_MEASUREMENT_1, 1.4, COL_MEASUREMENT_2, 1.4, COL_MEASUREMENT_3, 1.4, COL_MEASUREMENT_4, 1.4,
                      COL_CALCULATED_A, 0.0, COL_CALCULATED_B, 0.0, -1);
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   return GTK_TREE_MODEL(sampleCalcTable);
}
