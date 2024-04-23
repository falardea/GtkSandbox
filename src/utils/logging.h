/*
 * Created by falar on 2/24/2024.
*/
#ifndef GTKSANDBOX_LOGGING_H
#define GTKSANDBOX_LOGGING_H

#include <stdarg.h>
#include "../common_defs.h"

#define LOG_INFO(format, ...) logging_llprintf(LOGLEVEL_INFO, "%s: %s\n", __func__, format __VA_OPT__(,) __VA_ARGS__)
#define LOG_DEBUG(format, ...) logging_llprintf(LOGLEVEL_DEBUG, "%s: %s\n", __func__, format __VA_OPT__(,) __VA_ARGS__)
#define LOG_ERROR(format, ...) logging_llprintf(LOGLEVEL_ERROR, "%s: %s\n", __func__, format __VA_OPT__(,) __VA_ARGS__)

const char *strLoglevel(LOGLEVEL_T loglevelT);
int logging_llprintf(LOGLEVEL_T logLevel, const char *_format, ...);

#endif  /* GTKSANDBOX_LOGGING_H */
