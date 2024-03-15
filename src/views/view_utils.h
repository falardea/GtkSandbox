/*
 * Created by french on 3/14/24.
*/
#ifndef GTKSANDBOX_VIEW_UTILS_H
#define GTKSANDBOX_VIEW_UTILS_H
#include <gtk/gtk.h>

void vu_set_float_entry_text(GtkEntry *destination, const char *float_format, float value);
void vu_clear_float_entry_text(GtkEntry *destination, const char *float_format, float *default_value);

void vu_set_time_widget_text(GtkWidget *destination, const char *datetime_format, struct tm *source);
void vu_clear_time_widget_text(GtkWidget *destination, const char *with_format, const char *default_value);

#endif  /* GTKSANDBOX_VIEW_UTILS_H */
