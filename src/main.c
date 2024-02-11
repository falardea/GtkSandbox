#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include "utils/os_interface.h"
#include "models/app_model.h"
#include "controllers/app_ctrl.h"
#include "views/common/view_builder.h"
#include "views/common/view_styler.h"

extern ApplicationModel gAppModel;
AppWidgets_T *g_appWidgetsT;

int main(int argc, char **argv)
{
    bool app_success = true;

    app_init(argc, argv, &gAppModel);

    app_success = setDisplayEnv();  // TODO: move to app controller init

    gtk_init(&argc, &argv);

    g_appWidgetsT = build_application();
    applyApplicationStyle(g_appWidgetsT);

    gtk_main();

    g_print("Hello, World!\n");
    return app_success;
}
