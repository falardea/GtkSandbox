//
// Created by french on 2/3/24.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sys_interface.h"
#include "common_defs.h"
#include "logging.h"

RVALUE_T setDisplayEnv(void) {
   char *displayEnv;
   displayEnv = getenv("DISPLAY");
   if (displayEnv == NULL) {
      // Set up the command to get IP from os?
      char cmd[128];
      snprintf(cmd, sizeof(cmd), "grep nameserver /etc/resolv.conf | sed 's/nameserver //'");
      // Execute
      FILE *pF;
      pF = popen(cmd, "r");
      if (pF == NULL) {
         logging_llprint(LOGLEVEL_ERROR, "%s: trying to open cmd interface\n", __func__);
         return EXIT_FAILURE;
      }

      char retBuf[256];
      if (fgets(retBuf, 256, pF) == NULL) {
         logging_llprint(LOGLEVEL_ERROR, "%s: something went wrong reading cmd response\n", __func__);
         return EXIT_FAILURE;
      }
      retBuf[strcspn(retBuf, "\n")] = 0; // strip the newline

      char displayId[5] = {':', '0', '.', '0', '\n'};
      char nameserverStr[sizeof(retBuf) + sizeof(displayId)];

      snprintf(nameserverStr, sizeof(nameserverStr), "%s%s", retBuf, displayId);

      if (pclose(pF) != 0) {
         logging_llprint(LOGLEVEL_ERROR, "%s: closing cmd interface\n", __func__);
         return EXIT_FAILURE;
      }
      printf("setenv: DISPLAY=%s\n", nameserverStr);
      logging_llprint(LOGLEVEL_DEBUG, "%s: setenv: DISPLAY=%s\n", __func__, nameserverStr);

      return (setenv("DISPLAY", nameserverStr, false) ? EXIT_SUCCESS : EXIT_FAILURE);
   } else {
      return EXIT_SUCCESS;
   }
}

void getTimestamp(char *buf, size_t bufsz) {
   time_t current_time;
   struct tm *timeinfo;

   time(&current_time);
   timeinfo = localtime(&current_time);
   snprintf(buf, bufsz, "%d-%02d-%02dT%02d:%02d:%02d",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
