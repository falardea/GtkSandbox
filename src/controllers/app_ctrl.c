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

void app_init(int argc, char **argv)
{
    RVALUE_T retVal;

    retVal = parse_input_args(argc, argv);


    if (retVal == PARSE_ARG_ERR)
    {
        char timestamp[20];
        getTimestamp(timestamp, sizeof (timestamp));
//        printf("%s:%s: error parsing input args, exiting...\n", timestamp, __func__ );
        logging_llprint(LOGLEVEL_ERROR, "error parsing input args, exiting...\n");
        return;
    }

    logging_llprint(LOGLEVEL_DEBUG, "input arguments parsed successfully\n");
    // TODO: RVALUE_T returns?
    setDisplayEnv();

    gtk_init(&argc, &argv);


    g_appWidgetsT = build_application();
    applyApplicationStyle(g_appWidgetsT);
    setAppModelInitState(INIT_SUCCESS);
}
