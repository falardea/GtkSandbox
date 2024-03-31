//
// Created by french on 2/3/24.
//

#include "view_styler.h"

void applyApplicationStyle(__attribute__((unused)) AppWidgets_T *appWidgetsT) {
   GtkCssProvider *cssProvider = gtk_css_provider_new();

   gtk_css_provider_load_from_resource(cssProvider, "/sandbox/resources/style/sandbox_style.css");
   gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
   g_object_unref(cssProvider);
}
