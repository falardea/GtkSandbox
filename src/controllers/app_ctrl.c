//
// Created by french on 2/4/24.
//
#include <stdio.h>
#include <string.h>
#include "app_ctrl.h"
#include "../utils/os_interface.h"

void app_init(int argc, char **argv, ApplicationModel *appModel)
{
    setAppInitState(appModel, INIT_STARTED);

    print_usage(argv[0]);
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            printf("%s option recognized\n", argv[i]);
            setAppInitState(appModel, INIT_RUNNING);
        }
    }
    setAppInitState(appModel, INIT_SUCCESS);
}
