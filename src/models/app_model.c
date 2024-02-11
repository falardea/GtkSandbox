//
// Created by french on 2/3/24.
//
#include "app_model.h"

ApplicationModel gAppModel = {INIT_UNINITIALIZED, RUNTIME_INITIALIZING};

// A model interface might be nothing more than setter/getter functions for
// the singletons of model instances?
void setAppInitState(ApplicationModel *model, APP_INIT_STATE appInitState)
{
    model->initState = appInitState;
}
APP_INIT_STATE getAppInitState(ApplicationModel *model)
{
    return model->initState;
}
void setAppRuntimeState(ApplicationModel *model, APP_RUNTIME_STATE appRuntimeState)
{
    model->runtimeState = appRuntimeState;
}
APP_RUNTIME_STATE getAppRuntimeState(ApplicationModel *model)
{
    return model->runtimeState;
}

