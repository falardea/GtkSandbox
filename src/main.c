#include <gtk/gtk.h>
#include "models/app_model.h"
#include "controllers/app_ctrl.h"

extern ApplicationModel gAppModel;

int main(int argc, char **argv)
{
    app_init(argc, argv, &gAppModel);

    gtk_main();

    g_print("Hello, World!\n");
    return gAppModel.runtimeState;
}
