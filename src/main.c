#include <gtk/gtk.h>
#include "version.h"
#include "models/app_model.h"
#include "controllers/app_ctrl.h"
#include "utils/logging.h"

void exit_test(void) {
   logging_llprint(LOGLEVEL_DEBUG, "%s called as expected\n", __func__);
}

int main(int argc, char **argv) {
   printf("ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);

   app_init(argc, argv);

   if (getAppModelInitState() != INIT_ERROR) {
      logging_llprint(LOGLEVEL_DEBUG, "application initialized, starting UI\n");
      gtk_main();
      logging_llprint(LOGLEVEL_DEBUG, "UI closed, shutting down\n");

      exit_test();
   } else {
      setAppModelRuntimeState(RUNTIME_HANDLING_ERROR);
      logging_llprint(LOGLEVEL_ERROR, "application initialization failed, attempting a graceful shutdown\n");
      // Graceful shutdown stuff here
      setAppModelRuntimeState(RUNTIME_SHUTTING_DOWN);
   }
   return getAppModelRuntimeState();
}
