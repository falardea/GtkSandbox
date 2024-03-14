/*
 * Created by french on 3/14/24.
*/
#ifndef GTKSANDBOX_VIEW_UTILS_H
#define GTKSANDBOX_VIEW_UTILS_H
#include <gtk/gtk.h>

void view_utils_set_float_entry_formatted_text(GtkEntry *destination, const char *float_format, float value);
void view_utils_clear_float_entry_to_default(GtkEntry *destination, const char *float_format, float *default_value);


#endif  /* GTKSANDBOX_VIEW_UTILS_H */
