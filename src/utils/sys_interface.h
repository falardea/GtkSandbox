/*
 * Created by french on 2/3/24.
*/

#ifndef SANDBOX_OS_INTERFACE_H
#define SANDBOX_OS_INTERFACE_H

#include <stdbool.h>
#include "common_defs.h"

RVALUE_T setDisplayEnv(void);

void getTimestamp(char *buf, size_t bufsz);

#endif  /* SANDBOX_OS_INTERFACE_H */
