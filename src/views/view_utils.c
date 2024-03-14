/*
 * Created by french on 3/14/24.
*/
#include "view_utils.h"

void view_utils_set_float_entry_formatted_text(GtkEntry *destination, const char *float_format, float value)
{
   char display_string[20];
   snprintf(display_string, sizeof(display_string), float_format, value);
   gtk_entry_set_text(destination, display_string);
}

void view_utils_clear_float_entry_to_default(GtkEntry *destination, const char *float_format, float *default_value)
{
   if (default_value != NULL) /* We might have 0 defaults, so explicit NULL check, not just defined check*/
   {
      char display_string[20];
      snprintf(display_string, sizeof(display_string), float_format, default_value);
      gtk_entry_set_text(destination, display_string);
   }
   else
   {
      gtk_entry_set_text(destination, "");
   }
}
