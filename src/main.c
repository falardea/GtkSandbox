/*
 * Created by french sometime in early 2024.
*/
#include <gtk/gtk.h>
#include "version.h"
#include "models/app_model.h"
#include "controllers/app_ctrl.h"
#include "utils/logging.h"

#include "models/model_workflow.h"

extern WORKFLOW_STATE_T (*set_workflow_state[N_WORKFLOW_STATES])(void);
void exit_test(void) {
   LOG_DEBUG("called as expected");

   WORKFLOW_STATE_T currStep = STARTUP;
   while (currStep != SHUTDOWN && currStep != ERROR)
   {
      currStep = set_workflow_state[currStep]();
   }
}

gboolean some_task_on_timeout(__attribute__((unused)) gpointer user_data)
{  /* An example of a timeout function, just because I was playing with it...
    */
   LOG_INFO("CHECKPOINT");
   return G_SOURCE_REMOVE;
}


int main(int argc, char **argv) {
   printf("ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);

   gdk_threads_add_timeout(5000, (GSourceFunc )(some_task_on_timeout), NULL);

   app_init(argc, argv);

   if (getAppModelInitState() != INIT_ERROR) {

      LOG_DEBUG("application initialized, starting UI");
      gtk_main();
      LOG_DEBUG("UI closed, shutting down");

      exit_test();
   } else {
      setAppModelRuntimeState(RUNTIME_HANDLING_ERROR);
      LOG_ERROR("application initialization failed, attempting a graceful shutdown");
      // Graceful shutdown stuff here
      setAppModelRuntimeState(RUNTIME_SHUTTING_DOWN);
   }
   app_finalize();
   return getAppModelRuntimeState();
}
