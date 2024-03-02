//
// Created by french on 2/4/24.
//
#include <stdio.h>
#include "../common_defs.h"
#include "app_ctrl.h"
#include "../utils/sys_interface.h"
#include "../utils/parse_args.h"
#include "../utils/logging.h"
#include "views/common/view_builder.h"
#include "views/common/view_styler.h"

AppWidgets_T *g_appWidgetsT;

void app_init(int argc, char **argv) {
   RVALUE_T retVal;

   retVal = parse_input_args(argc, argv);

   if (retVal == PARSE_ARG_ERR) {
      setAppModelInitState(INIT_ERROR);
      logging_llprint(LOGLEVEL_ERROR, "error parsing input args, exiting...\n");
      return;
   }
   logging_llprint(LOGLEVEL_DEBUG, "arg parse success\n");

   retVal = setDisplayEnv();
   if (retVal == DISPLAY_ENV_ERR) {
      setAppModelInitState(INIT_ERROR);
      logging_llprint(LOGLEVEL_ERROR, "error setting DISPLAY env var, exiting...\n");
      return;
   }
   logging_llprint(LOGLEVEL_DEBUG, "DISPLAY set success\n");

   gtk_init(&argc, &argv);
   logging_llprint(LOGLEVEL_DEBUG, "gtk_init success\n");

   g_appWidgetsT = build_application();
   logging_llprint(LOGLEVEL_DEBUG, "build_application success\n");

   applyApplicationStyle(g_appWidgetsT);
   logging_llprint(LOGLEVEL_DEBUG, "applyApplicationStyle success\n");

   setAppModelInitState(INIT_SUCCESS);


}
