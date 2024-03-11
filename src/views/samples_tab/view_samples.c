/*
 * Created by french on 3/6/24.
*/
#define _XOPEN_SOURCE
#include <time.h>
#include "view_samples.h"
#include "../../models/model_samples.h"
#include "../root/view_msgout.h"



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
   g_object_set(cellRenderer, "cell-background", "white", "cell-background-set", TRUE, NULL);

   /* not using printLoglevelMsgOut here, since the "destination" is likely not completely setup */
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
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

void on_sample_selection_changed(GtkTreeSelection* self,
                                 gpointer user_data)
{
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_data;
   GtkTreeIter tableCursor;
   GtkTreeModel *samplesModel;
   gboolean enableEdit = FALSE;

   /* If there is a selection, this button should only be enabled if there is a selection */
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(self), &samplesModel, &tableCursor))
   {
      enableEdit = TRUE;
      gchararray timestamp;
      float m1, m2, m3, m4, cA, cB;
      char dispBuf[20];
      struct tm result;  // TODO: Maybe if we used a GDateTime in the TreeModel?

      gtk_tree_model_get(samplesModel, &tableCursor,
                         COL_TIMESTAMP, &timestamp,
                         COL_MEASUREMENT_1, &m1, COL_MEASUREMENT_2, &m2, COL_MEASUREMENT_3, &m3, COL_MEASUREMENT_4, &m4,
                         COL_CALCULATED_A, &cA, COL_CALCULATED_B, &cB,
                         -1);

      strptime(timestamp, "%Y-%0m-%0dT%0H:%0M:%0S", &result);
      gtk_calendar_select_month(GTK_CALENDAR(appWidgetsT->w_popCalendar), result.tm_mon, result.tm_year+1900);
      gtk_calendar_select_day(GTK_CALENDAR(appWidgetsT->w_popCalendar), result.tm_mday);
      strftime(dispBuf, sizeof(dispBuf), "%Y-%m-%d", &result);
      gtk_label_set_label(GTK_LABEL(appWidgetsT->w_lblSampleDate), dispBuf);
      strftime(dispBuf, sizeof(dispBuf), "%H", &result);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entrySampleHour), dispBuf);
      strftime(dispBuf, sizeof(dispBuf), "%M", &result);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entrySampleMinute), dispBuf);

      snprintf(dispBuf, sizeof(dispBuf), "%f", m1);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryMeasurement1), dispBuf);
      snprintf(dispBuf, sizeof(dispBuf), "%f", m2);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryMeasurement2), dispBuf);
      snprintf(dispBuf, sizeof(dispBuf), "%f", m3);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryMeasurement3), dispBuf);
      snprintf(dispBuf, sizeof(dispBuf), "%f", m4);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryMeasurement4), dispBuf);

      snprintf(dispBuf, sizeof(dispBuf), "%f", cA);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryCalculationA), dispBuf);
      snprintf(dispBuf, sizeof(dispBuf), "%f", cB);
      gtk_entry_set_text(GTK_ENTRY(appWidgetsT->w_entryCalculationB), dispBuf);

      free(timestamp);
   }
   gtk_widget_set_sensitive(GTK_WIDGET(appWidgetsT->w_btnEditSelection), enableEdit);
}

// Calendar popover
/* TODO: Should we be splitting this popover into it's own view?  Where does the menu callback go? */
void on_popDone_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_data;
   guint year, month, day;
   gtk_calendar_get_date(GTK_CALENDAR(appWidgetsT->w_popCalendar), &year, &month, &day);
   char tempDate[11];
   snprintf(tempDate, sizeof (tempDate), "%d-%02d-%02d\n", year, month+1, day);
   gtk_label_set_label(GTK_LABEL(appWidgetsT->w_lblSampleDate), tempDate);
   printLoglevelMsgOut(LOGLEVEL_DEBUG, tempDate);
   gtk_popover_popdown(GTK_POPOVER(appWidgetsT->w_ppvrDatepicker));
}

void on_popCancel_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{ /* On cancel, reset the GtkCalendar back to the time on the label*/
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_data;
   struct tm result;  // TODO: GDateTime?
   strptime(gtk_label_get_label(GTK_LABEL(appWidgetsT->w_lblSampleDate)),
            "%Y-%0m-%0d", &result);
   gtk_calendar_select_month(GTK_CALENDAR(appWidgetsT->w_popCalendar), result.tm_mon, result.tm_year+1900);
   gtk_calendar_select_day(GTK_CALENDAR(appWidgetsT->w_popCalendar), result.tm_mday);

   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_popover_popdown(GTK_POPOVER(appWidgetsT->w_ppvrDatepicker));
}

void on_editSampleDateTime_toggled(__attribute__((unused)) GtkMenuButton *mbutton, gpointer *user_data)
{
   if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(mbutton)))
   {
      printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: Set Calendar to value in label\n", __func__);
   } else {
      printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: don't do anything, the buttons will either set"
                                          "the label value, or leave it alone.\n", __func__);
   }

}
