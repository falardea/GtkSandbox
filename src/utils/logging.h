/*
 * Created by falar on 2/24/2024.
*/
#ifndef GTKSANDBOX_LOGGING_H
#define GTKSANDBOX_LOGGING_H

#include <stdarg.h>
#include "common_defs.h"

typedef enum {
   LOGLEVEL_DEBUG,
   LOGLEVEL_INFO,
   LOGLEVEL_ERROR
} LOGLEVEL_T;

int logging_llprint(LOGLEVEL_T logLevel, const char *_format, ...);

#endif  /* GTKSANDBOX_LOGGING_H */
