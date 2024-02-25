/*
 * Created by falar on 2/25/2024.
 */
#include <gtk/gtk.h>
#include <stdbool.h>
#include "child_view.h"
#include "utils/logging.h"

gboolean childWindowDelete(__attribute__((unused)) GtkWidget *eventSrc, __attribute__((unused)) GdkEvent *event,
                           __attribute__((unused)) gpointer data) {
   // TRUE to stop other handlers from being invoked for the event.
   // FALSE to propagate the event further
   return FALSE;
}

void childCloseButtonClicked(GtkWidget *btnSrc, __attribute__((unused)) gpointer *user_date) {
   gtk_window_close(GTK_WINDOW(gtk_widget_get_toplevel(btnSrc)));
}

void testBtnClicked(__attribute__((unused)) GtkWidget *btnSrc,
                    __attribute__((unused)) gpointer *user_date) {
   static int test_count = 1;
   static bool first = true;
   if (first) {
      logging_llprint(LOGLEVEL_DEBUG, "Testing... testing %d...\n", test_count);
      first = false;
   } else {
      logging_llprint(LOGLEVEL_DEBUG, "%d...\n", test_count);
   }
   test_count++;
}

void openChildGladeWnd(__attribute__((unused)) GtkWidget *parent,
                       __attribute__((unused)) gpointer *endowment)
{
   GtkWidget *ref_sandboxChildWnd;
   GtkBuilder *guiBuilder;

   guiBuilder = gtk_builder_new();

   if (gtk_builder_add_from_file(guiBuilder, "sandbox_child.glade", NULL) == 0)
   {
      logging_llprint(LOGLEVEL_ERROR, "%s: failed to load %s", __func__ , "sandbox_child.glade");
   }
   ref_sandboxChildWnd = GTK_WIDGET(gtk_builder_get_object(guiBuilder, "sandboxChildWnd"));
   gtk_builder_connect_signals(guiBuilder, NULL);
   gtk_widget_show_all(ref_sandboxChildWnd);
   g_object_unref(guiBuilder);
}


