/*
 * Created by french on 3/2/24.
*/
#include "globals.h"
#include "view_bound_toggles.h"
#include "views/root/view_msgout.h"

void on_tbBindingSrc_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: binding source is <%s>\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "active":"inactive");
}

void on_tbBiDirModelBoundEnable_toggled(GtkToggleButton *tbutton, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: Model Bound Toggle %s\n",
                   __func__,
                   gtk_toggle_button_get_active(tbutton) ? "Enabled":"Disabled");
}

void on_bPrintModelEnableState_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: modelDeviceA is %s\n",
                   __func__,
                   model_device_get_enabled(modelDeviceA) ? "enabled":"disabled");
}

void on_bUnboundModelEnable_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: enabling model\n", __func__);
   model_device_set_enabled(modelDeviceA, TRUE);
}

void on_bUnboundModelDisable_clicked(__attribute__((unused)) GtkButton *button, __attribute__((unused)) gpointer *user_data)
{
   printLoglevelMsgOut(LOGLEVEL_DEBUG, "%s: enabling model\n", __func__);
   model_device_set_enabled(modelDeviceA, FALSE);
}
