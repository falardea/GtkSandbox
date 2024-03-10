//
// Created by french on 2/4/24.
//
#include "app_ctrl.h"
#include "common_defs.h"
#include "globals.h"
#include "utils/sys_interface.h"
#include "utils/parse_args.h"
#include "utils/logging.h"
#include "views/view_builder.h"
#include "views/view_styler.h"
#include "models/app_model.h"

AppWidgets_T *g_appWidgetsT;
ModelDevice *modelDeviceA;
ModelDevice *modelDeviceB;

void app_init(int argc, char **argv) {
   RVALUE_T retVal;

   retVal = parse_input_args(argc, argv);
   if (retVal == PARSE_ARG_ERR) {
      setAppModelInitState(INIT_ERROR);
      logging_llprint(LOGLEVEL_ERROR, "error parsing input args, exiting...\n");
      return;
   }

   retVal = setDisplayEnv();
   if (retVal == DISPLAY_ENV_ERR) {
      setAppModelInitState(INIT_ERROR);
      logging_llprint(LOGLEVEL_ERROR, "error setting DISPLAY env var, exiting...\n");
      return;
   }

   modelDeviceA = model_device_new("device a");
   modelDeviceB = model_device_new("device b");

   gtk_init(&argc, &argv);

   g_appWidgetsT = build_application();
   logging_llprint(LOGLEVEL_DEBUG, "build_application success\n");

   applyApplicationStyle(g_appWidgetsT);
   logging_llprint(LOGLEVEL_DEBUG, "applyApplicationStyle success\n");

   setAppModelInitState(INIT_SUCCESS);
}

void app_finalize(void)
{
   g_object_unref(g_appWidgetsT->g_trslctnSelectedSample);
   g_object_unref(sampleCalcTable);
   g_object_unref(modelDeviceA);
   g_object_unref(modelDeviceB);
}
