/*
 * Created by french on 2/3/24.
*/
#include <stdio.h>
#include <stdbool.h>
#include "app_model.h"

// Thinking about making this static... would that make it a Singleton?
// A model interface might be nothing more than setter/getter functions
static ApplicationModel gAppModel = {INIT_UNINITIALIZED,
                                     RUNTIME_UNINITIALIZED,
                                     false,
                                     LOGLEVEL_ERROR};

void setAppModelInitState(APP_INIT_STATE appInitState) {
   gAppModel.initState = appInitState;
}

APP_INIT_STATE getAppModelInitState(void) {
   return gAppModel.initState;
}

void setAppModelRuntimeState(APP_RUNTIME_STATE appRuntimeState) {
   gAppModel.runtimeState = appRuntimeState;
}

APP_RUNTIME_STATE getAppModelRuntimeState(void) {
   return gAppModel.runtimeState;
}

void setAppModelDebuggingFlag(bool enable) {
   gAppModel.debuggingEnabled = enable;
   if (enable) {
      // TODO: set and immediately use log level?
      printf("Debugging Enabled\n");
   }
}

bool getAppModelDebuggingFlag(void) {
   return gAppModel.debuggingEnabled;
}

/**
 * setAppModelLoglevel
 * @param logLevel
 * If the model runtimeLoglevel is set to a lower level already, it does not get raised.  Once set, it's set for the
 * runtime life of the application.
 */
void setAppModelLoglevel(LOGLEVEL_T logLevel) {
   if (gAppModel.runtimeLoglevel > logLevel)
      gAppModel.runtimeLoglevel = logLevel;
}

LOGLEVEL_T getAppModelLoglevel(void) {
   return gAppModel.runtimeLoglevel;
}
