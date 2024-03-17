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
   logging_llprintf(LOGLEVEL_DEBUG, "%s called as expected\n", __func__);

   WORKFLOW_STATE_T currStep = STARTUP;
   while (currStep != SHUTDOWN && currStep != ERROR)
   {
      currStep = set_workflow_state[currStep]();
   }
}

GSourceFunc some_task_on_timeout(gpointer user_data)
{  /* An example of a timeout function, just because I was playing with it...
    */
   logging_llprintf(LOGLEVEL_INFO, "%s: CHECKPOINT \n", __func__);
   return G_SOURCE_REMOVE;
}


int main(int argc, char **argv) {
   printf("ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);

   g_timeout_add(5000, (GSourceFunc)some_task_on_timeout, NULL);

   app_init(argc, argv);

   if (getAppModelInitState() != INIT_ERROR) {

      logging_llprintf(LOGLEVEL_DEBUG, "application initialized, starting UI\n");
      gtk_main();
      logging_llprintf(LOGLEVEL_DEBUG, "UI closed, shutting down\n");

      exit_test();
   } else {
      setAppModelRuntimeState(RUNTIME_HANDLING_ERROR);
      logging_llprintf(LOGLEVEL_ERROR, "application initialization failed, attempting a graceful shutdown\n");
      // Graceful shutdown stuff here
      setAppModelRuntimeState(RUNTIME_SHUTTING_DOWN);
   }
   app_finalize();
   return getAppModelRuntimeState();
}
