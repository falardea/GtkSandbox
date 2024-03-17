/*
 * Created by french on 3/6/24.
*/
#define _XOPEN_SOURCE
#include <time.h>
#include <math.h>
#include "../view_utils.h"
#include "view_samples.h"
#include "../../models/model_samples.h"
#include "../root/view_msgout.h"
#include "utils/logging.h"

static void set_row_entries_view(SamplesRow_T *row, AppWidgets_T *wdgts)
{
   struct tm tm_of_timestamp;
   strptime(row->timestampStr, "%Y-%0m-%0dT%0H:%0M:%0S", &tm_of_timestamp);
   logging_llprintf(LOGLEVEL_DEBUG, "%s: CHECKPOINT: %s \n", __func__, row->timestampStr);

   gtk_calendar_select_month(GTK_CALENDAR(wdgts->w_popCalendar), tm_of_timestamp.tm_mon, tm_of_timestamp.tm_year + 1900);
   gtk_calendar_select_day(GTK_CALENDAR(wdgts->w_popCalendar), tm_of_timestamp.tm_mday);
   vu_set_time_widget_text(GTK_WIDGET(wdgts->w_lblSampleDate), "%Y-%m-%d", &tm_of_timestamp);
   vu_set_time_widget_text(GTK_WIDGET(wdgts->w_entrySampleHour), "%H", &tm_of_timestamp);
   vu_set_time_widget_text(GTK_WIDGET(wdgts->w_entrySampleMinute), "%M", &tm_of_timestamp);

   vu_set_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement1), "%0.2f", row->measurement1);
   vu_set_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement2), "%0.2f", row->measurement1);
   vu_set_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement3), "%0.2f", row->measurement1);
   vu_set_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement4), "%0.2f", row->measurement1);

   vu_set_double_widget_text(GTK_WIDGET(wdgts->w_entryCalculationA), "%0.2f", row->calculationA);
   vu_set_double_widget_text(GTK_WIDGET(wdgts->w_entryCalculationB), "%0.2f", row->calculationA);
}

static void clear_row_entries_view(AppWidgets_T *wdgts)
{
   time_t now;
   time(&now);
   struct tm tm_of_now;
   memcpy(&tm_of_now, gmtime(&now), sizeof(struct tm)); // so we don't have any race conditions?
   gtk_calendar_select_month(GTK_CALENDAR(wdgts->w_popCalendar), tm_of_now.tm_mon, tm_of_now.tm_year+1900);
   gtk_calendar_select_day(GTK_CALENDAR(wdgts->w_popCalendar), tm_of_now.tm_mday);

   vu_clear_time_widget_text(GTK_WIDGET(wdgts->w_lblSampleDate), "%s", "YYYY-MM-DD");
   vu_clear_time_widget_text(GTK_WIDGET(wdgts->w_entrySampleHour), NULL, NULL);
   vu_clear_time_widget_text(GTK_WIDGET(wdgts->w_entrySampleMinute), NULL, NULL);

   float defaultClearedValue = 0.0f;
   vu_clear_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement1), "%0.1f", &defaultClearedValue);
   vu_clear_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement2), NULL, NULL);
   vu_clear_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement3), NULL, NULL);
   vu_clear_float_widget_text(GTK_WIDGET(wdgts->w_entryMeasurement4), NULL, NULL);
   vu_clear_double_widget_text(GTK_WIDGET(wdgts->w_entryCalculationA), NULL, NULL);
   vu_clear_double_widget_text(GTK_WIDGET(wdgts->w_entryCalculationB), NULL, NULL);
}

void calcA_measurement_average(__attribute__((unused)) GtkTreeViewColumn   *col,
                               GtkCellRenderer     *renderer,
                               GtkTreeModel        *model,
                               GtkTreeIter         *rowCursor,
                               __attribute__((unused)) gpointer            user_data)
{
   float m1, m2, m3, m4, average;
   char strAverage[20];
   gtk_tree_model_get(model, rowCursor,
                      COL_MEASUREMENT_1, &m1, COL_MEASUREMENT_2, &m2, COL_MEASUREMENT_3, &m3, COL_MEASUREMENT_4, &m4,
                      -1);
   /* TODO: VALIDATION!! */
   average = (m1 + m2 + m3 + m4)/4;
   snprintf(strAverage, sizeof(strAverage), "%0.1f", average);
   g_object_set(renderer, "text", strAverage, NULL);
}

void calcB_measurement_max(__attribute__((unused)) GtkTreeViewColumn   *col,
                               GtkCellRenderer     *renderer,
                               GtkTreeModel        *model,
                               GtkTreeIter         *rowCursor,
                               __attribute__((unused)) gpointer            user_data)
{
   float m1, m2, m3, m4, Max;
   char strMax[20];
   gtk_tree_model_get(model, rowCursor,
                      COL_MEASUREMENT_1, &m1, COL_MEASUREMENT_2, &m2, COL_MEASUREMENT_3, &m3, COL_MEASUREMENT_4, &m4,
                      -1);
   /* TODO: VALIDATION!! */
   Max = (m1 > m2) ? m1 : m2;
   Max = (Max > m3) ? Max : m3;
   Max = (Max > m4) ? Max : m4;

   snprintf(strMax, sizeof(strMax), "%0.1f", Max);
   g_object_set(renderer, "text", strMax, NULL);
}

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


   gtk_tree_view_insert_column_with_data_func(GTK_TREE_VIEW(samplesTable), -1, "CalcA",
                                               cellRenderer, calcA_measurement_average, NULL, NULL);

   gtk_tree_view_insert_column_with_data_func(GTK_TREE_VIEW(samplesTable), -1, "CalcB",
                                               cellRenderer, calcB_measurement_max, NULL, NULL);

   g_object_set(cellRenderer, "cell-background", "white", "cell-background-set", TRUE, NULL);

   /* Set a function for the cal columns */

   /* not using printLoglevelMsgOut here, since the "destination" is likely not completely setup */
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
}

void on_btnEditSelection_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   GtkTreeModel *samplesModel;

   /* If there is a selection, this button should only be enabled if there is a selection */
   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(wdgts->g_trslctnSelectedSample),
                                        &samplesModel,
                                        &tableCursor))
   {
      /* Get the selection */
      /* tableCursor is set if there is a selection */
      gchararray timestamp;
      float m1, m2, m3, m4;
      gtk_tree_model_get(samplesModel, &tableCursor,
                         COL_TIMESTAMP, &timestamp,
                         COL_MEASUREMENT_1, &m1,
                         COL_MEASUREMENT_2, &m2,
                         COL_MEASUREMENT_3, &m3,
                         COL_MEASUREMENT_4, &m4,
                         -1);

      printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s:SAMPLE:>>%s|%f|%f|%f|%f\n", __func__,
                          timestamp, m1, m2, m3, m4);
      free(timestamp);
   }
}
void on_sample_selection_changed(GtkTreeSelection* self, gpointer user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   GtkTreeModel *samplesModel;
   gboolean enableEdit = FALSE;

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(self), &samplesModel, &tableCursor))
   {
      enableEdit = TRUE;
      SamplesRow_T row;
      get_selected_sample(&tableCursor, &row);
      set_row_entries_view(&row, wdgts);
   }
   else
   {
      clear_row_entries_view(wdgts);
   }
   gtk_widget_set_sensitive(GTK_WIDGET(wdgts->w_btnEditSelection), enableEdit);
}
void on_editSampleDateTime_toggled(__attribute__((unused)) GtkMenuButton *mbutton, __attribute__((unused)) gpointer *user_data)
{
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mbutton)))
   {
      printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: is there anything to do here?\n", __func__);
   } else {
      printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: don't do anything.\n", __func__);
   }
}
void on_btnDeleteRow_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_popover_popup(GTK_POPOVER(wdgts->w_ppvrAreYouSure));
}
void on_btnAreYouSureConfirm_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_popover_popdown(GTK_POPOVER(wdgts->w_ppvrAreYouSure));
}
void on_btnAreYouSureCancel_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_popover_popdown(GTK_POPOVER(wdgts->w_ppvrAreYouSure));
}
void on_btnCreateRow_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   time_t now;
   time(&now);
   struct tm tm_of_now;
   memcpy(&tm_of_now, gmtime(&now), sizeof(struct tm)); // so we don't have any race conditions?

   SamplesRow_T blank;
   strftime(blank.timestampStr, sizeof(blank.timestampStr), "%Y-%m-%dT%H:%M:%S", &tm_of_now);
   blank.measurement1 = NAN;
   blank.measurement2 = NAN;
   blank.measurement3 = NAN;
   blank.measurement4 = NAN;
   blank.calculationA = NAN;
   blank.calculationB = NAN;

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: CHECKPOINT %s \n", __func__, blank.timestampStr);
   create_new_sample(&blank);
   //TODO: post addition sort?
}
void on_btnChangeRow_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s:enter\n", __func__);
   AppWidgets_T *wdgts = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   gtk_tree_selection_get_selected (GTK_TREE_SELECTION(wdgts->g_trslctnSelectedSample), NULL, &tableCursor);

   SamplesRow_T row;
   get_selected_sample(&tableCursor, &row);

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", row.timestampStr);

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s:exit\n", __func__);
}
void on_btnCancelRowChange_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
}

// Calendar popover
/* TODO: Should we be splitting this popover into it's own view?  Where does the menu callback go? */
void on_popDone_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *)user_data;
   guint year, month, day;
   gtk_calendar_get_date(GTK_CALENDAR(wdgts->w_popCalendar), &year, &month, &day);
   char tempDate[11];
   snprintf(tempDate, sizeof (tempDate), "%d-%02d-%02d\n", year, month+1, day);
   gtk_label_set_label(GTK_LABEL(wdgts->w_lblSampleDate), tempDate);
   printLoglevelMsgOut(LOGLEVEL_DEBUG, tempDate);
   gtk_popover_popdown(GTK_POPOVER(wdgts->w_ppvrDatepicker));
}
void on_popCancel_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{ /* On cancel, reset the GtkCalendar back to the time on the label*/
   AppWidgets_T *wdgts = (AppWidgets_T *)user_data;
   struct tm result;  // TODO: GDateTime?
   strptime(gtk_label_get_label(GTK_LABEL(wdgts->w_lblSampleDate)),
            "%Y-%0m-%0d", &result);
   gtk_calendar_select_month(GTK_CALENDAR(wdgts->w_popCalendar), result.tm_mon, result.tm_year+1900);
   gtk_calendar_select_day(GTK_CALENDAR(wdgts->w_popCalendar), result.tm_mday);

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_popover_popdown(GTK_POPOVER(wdgts->w_ppvrDatepicker));
}
