#include <gtk/gtk.h>
#include "models/app_model.h"
#include "controllers/app_ctrl.h"

int main(int argc, char **argv)
{
    app_init(argc, argv);
    if (getAppModelInitState() != INIT_ERROR)
    {
        gtk_main();
    }
    else
    {
        setAppModelRuntimeState(RUNTIME_HANDLING_ERROR);
        // Graceful shutdown stuff here
        setAppModelRuntimeState(RUNTIME_SHUTTING_DOWN);
    }
    return getAppModelRuntimeState();
}
