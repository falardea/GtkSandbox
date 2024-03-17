/*
 * Created by french on 3/17/24.
*/
#include "view_wizard.h"
#include "../../utils/logging.h"

void on_btn_HorizontalPair_next_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_GridPage);
}
void on_btn_HorizontalPair_back_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_HorizontalPair1);
}
void on_btn_GridPage_next_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_VerticalPair);
}
void on_btn_GridPage_back_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_HorizontalPair);
}
void on_btn_VerticalPair_back_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_GridPage);
}
void on_btn_VerticalPair_next_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_HorizontalPair1);
}
void on_btn_HorizontalPair_next1_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_HorizontalPair);
}
void on_btn_HorizontalPair_back1_clicked(__attribute__((unused)) GtkButton *button, gpointer *user_data)
{
   AppWidgets_T *wdgts = (AppWidgets_T *) user_data;
   logging_llprintf(LOGLEVEL_DEBUG, "%s\n", __func__);
   gtk_stack_set_visible_child(GTK_STACK(wdgts->w_stck_SetupWizard), wdgts->w_stckpg_VerticalPair);
}
