/*
 * Created by falar on 2/25/2024.
 */
#include <gtk/gtk.h>
#include <stdbool.h>
#include "globals.h"
#include "../root/view_msgout.h"
#include "view_app_child.h"
#include "utils/logging.h"

static uint32_t currentChildCount = 0;
static const uint32_t MAX_CHILDREN = 3;
static uint32_t clickCount = 0;

typedef enum
{
   DEFAULT,    // uninitialized
   NOT_READY,  // initialized (created), not show ready
   READY       // ready to show the user
} APP_READY_STATE;

typedef struct
{
   AppWidgets_T         *parent_widgets;
   APP_READY_STATE      *ready_state;
} ChildUserData_T;

/* We could malloc these too? */
ChildUserData_T childA;
ChildUserData_T childB;
ChildUserData_T childC;

gboolean childWindowDelete(__attribute__((unused)) GtkWidget *eventSrc, __attribute__((unused)) GdkEvent *event,
                           __attribute__((unused)) gpointer data) {
   // TRUE to stop other handlers from being invoked for the event.
   // FALSE to propagate the event further
   logging_llprintf(LOGLEVEL_DEBUG, "%s: decrementing child count\n", __func__);
   currentChildCount--;
   return FALSE;
}

void childCloseButtonClicked(GtkWidget *btnSrc, __attribute__((unused)) gpointer *user_date) {
   gtk_window_close(GTK_WINDOW(gtk_widget_get_toplevel(btnSrc)));
}

void testBtnClicked(__attribute__((unused)) GtkWidget *btnSrc,
                    __attribute__((unused)) gpointer *user_date) {
   static bool first = true;
   clickCount++;
   if (first) {
//   AppWidgets_T *widgets = (AppWidgets_T *) user_date;
//      gtk_container_child_set_property(widgets->w_stck_SetupWizard, setup_start_page, "label", "Yay!");
      printLoglevelMsgOut(LOGLEVEL_INFO, "Testing... testing %d...\n", clickCount);
      first = false;
   } else {
      printLoglevelMsgOut(LOGLEVEL_INFO, "%d...\n", clickCount);
   }
}

void openChildGladeWnd(__attribute__((unused)) GtkWidget *parent,
                       gpointer *endowment)
{
   GtkWidget *ref_sandboxChildWnd;
   GtkBuilder *guiBuilder;

   guiBuilder = gtk_builder_new();
   if (gtk_builder_add_from_resource(guiBuilder, "/sbc/resources/sandbox_child.glade", NULL) == 0)
   {
      printLoglevelMsgOut(LOGLEVEL_ERROR, "%s: failed to load resource %s", __func__ , "sandbox_child.glade");
   }
   ref_sandboxChildWnd = GTK_WIDGET(gtk_builder_get_object(guiBuilder, "sandboxChildWnd"));

   /* TODO: perhaps we put the parent's endowment (user_data) into a different struct for the child and add other flavorings? */
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

