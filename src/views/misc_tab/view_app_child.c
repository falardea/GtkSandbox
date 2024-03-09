/*
 * Created by falar on 2/25/2024.
 */
#include <gtk/gtk.h>
#include <stdbool.h>
#include "globals.h"
#include "view_app_child.h"
#include "utils/logging.h"

static uint32_t currentChildCount = 0;
static const uint32_t MAX_CHILDREN = 3;
static uint32_t clickCount = 0;

static void printMsgToParent(AppWidgets_T *appWidgetsT, gchar *buf)
{
   GtkTextBuffer  *tvBuff  =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(appWidgetsT->w_tvChildMsgOutViewer));
   GtkTextIter    endIter;
   gtk_text_buffer_get_end_iter(tvBuff, &endIter);

   logging_llprint(LOGLEVEL_DEBUG, "%s: checkpoint: (tvBuff != NULL) = %s \n",
                   __func__, (tvBuff != NULL) ? "true":"false");

   gtk_text_buffer_insert(tvBuff, &endIter, buf, -1);
}

gboolean childWindowDelete(__attribute__((unused)) GtkWidget *eventSrc, __attribute__((unused)) GdkEvent *event,
                           __attribute__((unused)) gpointer data) {
   // TRUE to stop other handlers from being invoked for the event.
   // FALSE to propagate the event further
   logging_llprint(LOGLEVEL_DEBUG, "%s: decrementing child count\n", __func__);
   currentChildCount--;
   return FALSE;
}

void childCloseButtonClicked(GtkWidget *btnSrc, __attribute__((unused)) gpointer *user_date) {
   gtk_window_close(GTK_WINDOW(gtk_widget_get_toplevel(btnSrc)));
}

void testBtnClicked(__attribute__((unused)) GtkWidget *btnSrc,
                    gpointer *user_date) {
   AppWidgets_T *appWidgetsT = (AppWidgets_T *)user_date;

   static bool first = true;
   clickCount++;
   if (first) {
      char buf[120];
      snprintf(buf, sizeof(buf), "Testing... testing %d...\n", clickCount);
      printMsgToParent(appWidgetsT, buf);
      logging_llprint(LOGLEVEL_DEBUG, buf);

      first = false;
   } else {
      char buf[120];
      snprintf(buf, sizeof(buf), "%d...\n", clickCount);
      printMsgToParent(appWidgetsT, buf);
      logging_llprint(LOGLEVEL_DEBUG, buf);
   }
}

void openChildGladeWnd(__attribute__((unused)) GtkWidget *parent,
                       gpointer *endowment)
{
   GtkWidget *ref_sandboxChildWnd;
   GtkBuilder *guiBuilder;

   guiBuilder = gtk_builder_new();

   if (gtk_builder_add_from_file(guiBuilder, "sandbox_child.glade", NULL) == 0)
   {
      logging_llprint(LOGLEVEL_ERROR, "%s: failed to load %s", __func__ , "sandbox_child.glade");
   }
   ref_sandboxChildWnd = GTK_WIDGET(gtk_builder_get_object(guiBuilder, "sandboxChildWnd"));
   gtk_builder_connect_signals(guiBuilder, endowment);
   currentChildCount++;
   gtk_widget_show_all(ref_sandboxChildWnd);
   g_object_unref(guiBuilder);
}

void launchChildWnd(GtkWidget *btnSrc, gpointer *user_data)
{
   if (currentChildCount < MAX_CHILDREN)
   {
      openChildGladeWnd(gtk_widget_get_toplevel(btnSrc), user_data);
   }
}

