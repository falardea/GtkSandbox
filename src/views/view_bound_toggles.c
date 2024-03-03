/*
 * Created by french on 3/2/24.
*/
//#include "common_defs.h"
#include "globals.h"
#include "utils/logging.h"
#include "view_bound_toggles.h"
//#include "models/model_device.h"

void on_tbBindingSrc_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   logging_llprint(LOGLEVEL_DEBUG, "%s: binding source is <%s>\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "active":"inactive");
}

void on_tbBoundTarget1_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   logging_llprint(LOGLEVEL_DEBUG, "%s: binding target 1 is <%s>\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "active":"inactive");
}

void on_tbBoundTarget2_toggled(__attribute__((unused)) GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   logging_llprint(LOGLEVEL_DEBUG, "%s: modelDeviceA is <%s>\n",
                   __func__,
                   model_device_get_enabled(modelDeviceA) ? "enabled":"disabled");
}

void on_tbModelToggle_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   logging_llprint(LOGLEVEL_DEBUG, "%s: model toggling\n", __func__);
   model_device_set_enabled(modelDeviceA, gtk_toggle_button_get_active(tbutton));
}
