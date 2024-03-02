/*
 * Created by falar on 2/24/2024.
*/
#include <stdio.h>
#include "../models/app_model.h"
#include "sys_interface.h"
#include "logging.h"

const char *DEBUG_STR = "DEBUG";
const char *INFO_STR = "INFO";
const char *ERROR_STR = "ERROR";
static char timestamp[20];  // not sure why it felt better to allocate the memory once

const char *strLoglevel(LOGLEVEL_T loglevelT) {
   if (loglevelT == LOGLEVEL_ERROR)
      return ERROR_STR;
   else if (loglevelT == LOGLEVEL_INFO)
      return INFO_STR;
   else
      return DEBUG_STR;
}

int logging_llprint(LOGLEVEL_T logLevel, const char *_format, ...) {
   int done = 0;
   if (logLevel >= getAppModelLoglevel()) {
      // This is effectively a copy of stdio.printf, with a filter for log level
      // Probably not a "production" way of doing this, but it's a sandbox, so meh
      va_list arg;
      getTimestamp(timestamp, sizeof(timestamp));
      printf("%s:%s:", timestamp, strLoglevel(logLevel));
      va_start(arg, _format);
      done = vfprintf(stdout, _format, arg);
      va_end(arg);
      return done;
   }
   return done;
}
