//
// Created by french on 2/3/24.
//

#ifndef SANDBOX_APP_MODEL_H
#define SANDBOX_APP_MODEL_H
#include <stdbool.h>

typedef enum {
    INIT_UNINITIALIZED,
    INIT_STARTED,
    INIT_RUNNING,
    INIT_SUCCESS,
    INIT_ERROR
} APP_INIT_STATE;

typedef enum {
    RUNTIME_UNINITIALIZED,
    RUNTIME_INITIALIZING,
    RUNTIME_RUNNING_NORMALLY,
    RUNTIME_HANDLING_ERROR,
    RUNTIME_RUNNING_DEPRECATED,
    RUNTIME_RUNNING_SAFE_MODE,
    RUNTIME_SHUTTING_DOWN,
} APP_RUNTIME_STATE;

typedef struct {
    APP_INIT_STATE      initState;
    APP_RUNTIME_STATE   runtimeState;
} ApplicationModel;

extern ApplicationModel gAppModel;

void setAppInitState(ApplicationModel *model, APP_INIT_STATE appInitState);
APP_INIT_STATE getAppInitState(ApplicationModel *model);
void setAppRuntimeState(ApplicationModel *model, APP_RUNTIME_STATE appInitState);
APP_RUNTIME_STATE getAppRuntimeState(ApplicationModel *model);

#endif //SANDBOX_APP_MODEL_H
