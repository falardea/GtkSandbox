/*
 * Created by french on 3/6/24.
*/
#ifndef GTKSANDBOX_MODEL_SAMPLES_H
#define GTKSANDBOX_MODEL_SAMPLES_H
#include <gtk/gtk.h>

typedef enum {
   COL_TIMESTAMP = 0,
   COL_MEASUREMENT_1,
   COL_MEASUREMENT_2,
   COL_MEASUREMENT_3,
   COL_MEASUREMENT_4,
   COL_CALCULATED_A,
   COL_CALCULATED_B,
   NUM_SAMPLES_COLUMNS
} SAMPLES_COLUMNS_T;

GtkTreeModel *build_samples_model(void);

#endif  /* GTKSANDBOX_MODEL_SAMPLES_H */
