#include <gtk/gtk.h>
#include "version.h"
#include "models/app_model.h"
#include "controllers/app_ctrl.h"

int main(int argc, char **argv)
{
    printf("ver.%d.%d.%d\n", project_VERSION_MAJOR, project_VERSION_MINOR, project_VERSION_PATCH);
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
