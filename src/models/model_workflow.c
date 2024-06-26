/*
 * Created by french on 3/2/24.
*/
#include <stdint.h>
#include "common_defs.h"
#include "../utils/logging.h"
#include "model_workflow.h"

static uint8_t nWorkflowSteps = 0;
WORKFLOW_STATE_T (*set_workflow_state[N_WORKFLOW_STATES])(void) =
{
   [STARTUP] =       (&handle_startup),
   [INIT_HW] =       (&handle_init_hw),
   [INIT_CONTROL] =  (&handle_init_control),
   [RUNNING] =       (&handle_running),
   [STOPPING] =      (&handle_stopping),
   [ERROR] =         (&handle_error),
   [SHUTDOWN] =      (&handle_shutdown)
};

static void setWorkflowStepCount(uint8_t nSteps)
{
   LOG_DEBUG("setting workflow step count to %u", nSteps);
   nWorkflowSteps = nSteps;
}

static uint8_t getWorkflowStepCount(void)
{
   return nWorkflowSteps;
}

WORKFLOW_STATE_T handle_startup(void)
{
   LOG_DEBUG("");
   return INIT_HW;
}

WORKFLOW_STATE_T handle_init_hw(void)
{
   LOG_DEBUG("");
   return INIT_CONTROL;
}

WORKFLOW_STATE_T handle_init_control(void)
{
   LOG_DEBUG("");
   return RUNNING;
}

WORKFLOW_STATE_T handle_running(void)
{
   LOG_DEBUG("");
   while(getWorkflowStepCount() > 0)
   {
      setWorkflowStepCount(getWorkflowStepCount() - 1);
      return RUNNING;
   }
   return STOPPING;
}

WORKFLOW_STATE_T handle_stopping(void)
{
   LOG_DEBUG("");
   return SHUTDOWN;
}

WORKFLOW_STATE_T handle_error(void)
{
   LOG_DEBUG("");
   return SHUTDOWN;
}

WORKFLOW_STATE_T handle_shutdown(void)
{
   LOG_DEBUG("");
   return SHUTDOWN;
}
