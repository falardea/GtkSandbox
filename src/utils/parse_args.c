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
    const char *exeName = strrchr(argv, '/') + 1;  // the +1 removes the leading '/'
    printf("Usage: %s\n"
           "A sandbox project for experimenting with GTK3 and design patterns in C.\n"
           " -D\tEnable Debugging (currently unused)\n\n\n", exeName);
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
