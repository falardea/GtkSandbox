//
// Created by french on 2/17/24.
//
#include <stdio.h>
#include <string.h>
#include "../version.h"
#include "../common_defs.h"
#include "../models/app_model.h"
#include "parse_args.h"

static void print_usage(char *argv)
{
    printf("%s(%d.%d.%d)\n", argv, project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);
}

RVALUE_T parse_input_args(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-D") == 0)
        {
            setAppModelDebuggingFlag(true);
        }
        else if (strlen(argv[i]) > 0)
        {
            print_usage(argv[0]);
            setAppModelInitState(INIT_ERROR);
            return PARSE_ARG_ERR;
        }
    }
    return SUCCESS;
}
