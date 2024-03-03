/*
 * Created by french on 3/2/24.
*/
#ifndef GTKSANDBOX_MODEL_WORKFLOW_H
#define GTKSANDBOX_MODEL_WORKFLOW_H

typedef enum
{
   STARTUP = 0,
   INIT_HW,
   INIT_CONTROL,
   RUNNING,
   STOPPING,
   ERROR,
   SHUTDOWN,
   N_WORKFLOW_STATES
} WORKFLOW_STATE_T;

WORKFLOW_STATE_T handle_startup(void);
WORKFLOW_STATE_T handle_init_hw(void);
WORKFLOW_STATE_T handle_init_control(void);
WORKFLOW_STATE_T handle_running(void);
WORKFLOW_STATE_T handle_stopping(void);
WORKFLOW_STATE_T handle_error(void);
WORKFLOW_STATE_T handle_shutdown(void);

#endif  /* GTKSANDBOX_MODEL_WORKFLOW_H */
