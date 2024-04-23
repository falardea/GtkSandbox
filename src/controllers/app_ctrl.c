//
// Created by french on 2/4/24.
//
#include "app_ctrl.h"
#include "common_defs.h"
#include "globals.h"
#include "ctrl_samples.h"
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
      LOG_ERROR("error parsing input args, exiting...");
      return;
   }

   retVal = setDisplayEnv();
   if (retVal == DISPLAY_ENV_ERR) {
      setAppModelInitState(INIT_ERROR);
      LOG_ERROR("error setting DISPLAY env var, exiting...");
      return;
   }

   modelDeviceA = model_device_new("device a");
   modelDeviceB = model_device_new("device b");

   gtk_init(&argc, &argv);

   g_appWidgetsT = build_application();
   LOG_DEBUG("build_application success");

   applyApplicationStyle(g_appWidgetsT);
   LOG_DEBUG("applyApplicationStyle success");

   load_sample_data_from_file();

   setAppModelInitState(INIT_SUCCESS);
}

void app_finalize(void)
{
   g_object_unref(g_appWidgetsT->g_trslctnSelectedSample);
   g_object_unref(sampleCalcTable);
   g_object_unref(modelDeviceA);
   g_object_unref(modelDeviceB);
}
