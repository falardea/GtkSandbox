/*
 * Created by french on 3/10/24.
*/
#ifndef GTKSANDBOX_VIEW_MSGOUT_H
#define GTKSANDBOX_VIEW_MSGOUT_H
#include <stdarg.h>
#include <gtk/gtk.h>
#include "../../common_defs.h"

void printLoglevelMsgOut(LOGLEVEL_T loglevel, const char *_format, ...);

#endif  /* GTKSANDBOX_VIEW_MSGOUT_H */
