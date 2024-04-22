/*
 * Created by french on 4/13/24.
*/
#ifndef GTKSANDBOX_SEARCH_WORKER_H
#define GTKSANDBOX_SEARCH_WORKER_H
#include <glib-object.h>
G_BEGIN_DECLS

#define SEARCH_TYPE_WORKER       ( search_worker_get_type( ) )

G_DECLARE_FINAL_TYPE(SearchWorker, search_worker, SEARCH, WORKER, GObject)

SearchWorker *search_worker_new( const gchar *timestamp );

gchar *search_worker_get_timestamp( SearchWorker *self );
void search_worker_set_timestamp( SearchWorker *self, const gchar *timestamp );

gboolean search_worker_run_lookup( SearchWorker *self, const gchar *timestamp);

G_END_DECLS
#endif  /* GTKSANDBOX_SEARCH_WORKER_H */
