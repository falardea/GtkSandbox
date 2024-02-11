//
// Created by french on 2/3/24.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../version.h"

#include "os_interface.h"

bool setDisplayEnv(void)
{
    char *displayEnv;
    displayEnv = getenv("DISPLAY");
    if (displayEnv == NULL)
    {
        // Set up the command to get IP from os?
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "grep nameserver /etc/resolv.conf | sed 's/nameserver //'");
        // Execute
        FILE *pF;
        pF = popen(cmd, "r");
        if(pF == NULL) {
            printf("Oops, something went wrong trying to find the IP\n");
            return false;
        }

        char retBuf[256];
        if (fgets(retBuf, 256, pF) != NULL)
        {
            printf("something went wrong reading the file\n");
        }
        retBuf[strcspn(retBuf, "\n")] = 0; // strip the newline

        char displayId[5] = {':', '0', '.', '0', '\n'};
        char nameserverStr[sizeof (retBuf) + sizeof (displayId)];

        snprintf(nameserverStr, sizeof (nameserverStr), "%s%s", retBuf, displayId);
        printf("setenv: DISPLAY=%s\n", nameserverStr);

        if(pclose(pF) != 0)
        {
            printf("Error closing command interface\n");
            return false;
        }

        return setenv("DISPLAY", nameserverStr, false);
    }
    else
    {
        return true;
    }
}
void print_usage(char *argv)
{
    printf("%s(%d.%d.%d)\n", argv, project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);
//    std::cout << argv << " (v" << project_VERSION_MAJOR << "."
//              << project_VERSION_MINOR << "."
//              << project_VERSION_PATCH << ")" << std::endl;
//    std::cout << "Usage: " << argv << " <TBD>" << std::endl;
}
