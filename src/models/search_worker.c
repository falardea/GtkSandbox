/*
 * Created by french on 4/13/24.
*/
#include <glib-object.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

#include "search_worker.h"
#include "../utils/logging.h"

struct _SearchWorker
{
   GObject  parent_object;
   gchar    *timestamp;
};

G_DEFINE_TYPE( SearchWorker, search_worker, G_TYPE_OBJECT )

enum
{
   PROP_0, // Reserved for GObject
   PROP_TIMESTAMP,
   N_PROPERTIES
};

static void search_worker_finalize( GObject *self );

static void search_worker_set_property( GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec )
{
   SearchWorker *worker = SEARCH_WORKER( object );

   switch( prop_id ) {
      case PROP_TIMESTAMP:
         search_worker_set_timestamp( worker, g_value_get_string( value ) );
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID( object, prop_id, pspec );
   }
}

static void search_worker_get_property( GObject *object, guint prop_id, GValue *value, GParamSpec *pspec )
{
   SearchWorker *worker = SEARCH_WORKER( object );

   switch( prop_id ) {
      case PROP_TIMESTAMP:
         g_value_set_string( value, search_worker_get_timestamp( worker ) );
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID( object, prop_id, pspec );
   }
}

static GParamSpec *worker_properties[N_PROPERTIES] = {NULL, };

static void search_worker_class_init( SearchWorkerClass *klass )
{
   GObjectClass *gobject_class = G_OBJECT_CLASS( klass );

   gobject_class->finalize = search_worker_finalize;

   gobject_class->get_property = search_worker_get_property;
   gobject_class->set_property = search_worker_set_property;

   worker_properties[PROP_TIMESTAMP] = g_param_spec_string( "worker-timestamp",
                                                                "WorkerTimestamp",
                                                                "Worker Timestamp",
                                                                NULL,
                                                                G_PARAM_READWRITE );
   g_object_class_install_properties(gobject_class, N_PROPERTIES, worker_properties);
}

static void search_worker_init (SearchWorker *self )
{
   self->timestamp = g_strdup( "");
}

static void search_worker_finalize( GObject *self )
{
   SearchWorker *worker = SEARCH_WORKER( self );
   g_free ( worker->timestamp );
   GObjectClass *parent_class = G_OBJECT_CLASS ( search_worker_parent_class );
   ( *parent_class->finalize )( self );
}

SearchWorker  *search_worker_new( const gchar *timestamp )
{
   SearchWorker *worker;

   worker = SEARCH_WORKER( g_object_new( SEARCH_TYPE_WORKER, NULL ) );

   if( timestamp != NULL )
      search_worker_set_timestamp( worker, timestamp );

   return worker;
}

gchar *search_worker_get_timestamp( SearchWorker *self )
{
   g_return_val_if_fail(SEARCH_IS_WORKER( self ), NULL );

   return g_strdup( self->timestamp );
}

void search_worker_set_timestamp (SearchWorker *self, const gchar *timestamp )
{
   g_return_if_fail ( timestamp );
   g_return_if_fail (SEARCH_IS_WORKER( self ) );

   if (self->timestamp != NULL )
      g_free( self->timestamp );

   self->timestamp = g_strdup( timestamp );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * char *date_lookup[] = {"2024-01-23 04:31",
                             "2024-02-23 05:56",
                             "2024-03-23 07:17",
                             "2024-04-23 08:11",
                             "2024-05-23 12:34",
                             "2024-06-23 14:16",
                             "2024-07-23 21:37"
      };
      for (size_t i = 0; i < ( sizeof(date_lookup) / sizeof(date_lookup[0]) ); i++)
      {
         LOG_DEBUG(""Looking for %s\n", date_lookup[i]);
         parse_psuedo_csv(date_lookup[i]);
      }
 * */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void on_btnEmployWorker_clicked(GtkButton *btn, gpointer user_data)
{
   LOG_DEBUG("CHECKPOINT");
}

char *search_string[] = {"Date,Ticks,Notes,field1,field2,field3,field4,field5,field6,field7,field8",
                         "2024-01-23 04:31:12,12341,\"aaaddd\",1,1,1,1,1,1,1,8.123\n",
                         "2024-02-23 05:56:32,12342,\"This line in the csv can have commas, and even comma\n",
                         "\n",
                         "seperated numbers, like: 1,2,3,4,5,a string,and,carriage returns, and more numbers: \n",
                         "not a date here though\",1,2,2,2,2,2,2,8.234\n",
                         "2024-03-23 07:17:41,12343,\"1,2,3,4\",1,3,3,3,3,3,3,8.345\n",
                         "2024-04-23 08:11:34,12344,\"some text, no newline\",1,4,4,4,4,4,4,8.456\n",
                         "2024-05-23 12:34:57,12345,\"\n",
                         "some text, but not a newline\n",
                         "\",1,5,5,5,5,5,5,8.567\n",
                         "2024-06-23 14:16:40,12346,\"some text, but not a newline\",1,6,6,6,6,6,6,8.678\n",
                         "2024-07-23 21:37:04,12347,\"some text, but not a newline\",1,7,7,7,7,7,7,8.789\n"};


gboolean compile_regex(regex_t *re, const char *patt)
{
   /* Use REG_EXTENDED for POSIX regex notation */
   reg_errcode_t re_comp_ret = regcomp(re, patt, REG_EXTENDED);
   if (re_comp_ret != 0) {
      char err_buff[1024];
      regerror(re_comp_ret, re, err_buff, sizeof (err_buff));
      LOG_ERROR("'regcomp' failed to compile %s, reporting: %s", patt, err_buff);
      return FALSE;
   }
   return TRUE;
}

gboolean search_worker_run_lookup( SearchWorker *self, const gchar *timestamp)
{
   gboolean found = FALSE;
   char str_out[SHRT_MAX];  // assume we're limited to an Excel spreadsheet cell
   char re_patt[128];
   int so_ret = REG_NOMATCH;
   regex_t regx;
   regmatch_t pmatch[4]; // we re-use this, so we size to the largest

   /* Build the regex with the timestamp, up to the first quote, then look for an end quote, and group that if found */
   snprintf(re_patt, sizeof(re_patt), "(^%s:[0-9]{2},[0-9]+,\")(.*(\".*$))?", timestamp);

   if (!compile_regex(&regx, re_patt)){
      regfree(&regx);
      return FALSE;
   }

   for(size_t i = 0; i < (sizeof (search_string)/sizeof(search_string[0])); i++)
   {
      so_ret = regexec(&regx, search_string[i], 4, pmatch, 0);
      if (so_ret == 0)
      {
         strncpy(str_out, search_string[i], pmatch[1].rm_eo);
         str_out[pmatch[1].rm_eo] = 0;

         if (pmatch[2].rm_so != -1) {
            /* We have a complete csv line, we're going to drop the notes for cleanliness */
            int so_remain = (pmatch[3].rm_so != -1) ? pmatch[3].rm_so : pmatch[2].rm_so;
            int eo_remain = (pmatch[3].rm_eo != -1) ? pmatch[3].rm_eo : pmatch[2].rm_eo;

            strncpy(str_out + pmatch[1].rm_eo,
                    search_string[i] + so_remain,
                    eo_remain - so_remain);
            /* We're NOT null-terminated here, so we can't use strlen here */
            str_out[eo_remain - so_remain + pmatch[1].rm_eo - 1] = 0;
            found = TRUE;
            break;
         }
         else
         {
            /* Build the regex to find the end of our open quote, grouping the quote and remainder of the line */
            snprintf(re_patt, sizeof(re_patt), "^[^\"]*(\".*$)");

            if (!compile_regex(&regx, re_patt)){
               regfree(&regx);
               return FALSE;
            }

            for (size_t cont = i+1; cont < (sizeof (search_string)/sizeof(search_string[0])); cont++)
            {
               so_ret = regexec(&regx, search_string[cont], 2, pmatch, 0);
               if (so_ret == 0)
               {
                  size_t current_str_end = strlen(str_out);  // did we null terminate properly?
                  strncpy(str_out + current_str_end, /* overwrite the null-term */
                          search_string[cont] + pmatch[1].rm_so,
                          pmatch[1].rm_eo - pmatch[1].rm_so);
                  /* We're NOT null-terminated here, so we can't use strlen here */
                  str_out[current_str_end + pmatch[1].rm_eo - pmatch[1].rm_so - 1] = 0;
                  found = TRUE;
                  break;
               }
            }
            break;
         }
      }
   }
   if (found)
   {
      char *str_cursor;
      str_cursor = strtok(str_out, ",");
      while(str_cursor != NULL)
      {
         LOG_DEBUG("%s", str_cursor);
         str_cursor = strtok(NULL, ",");
      }
   }
   regfree(&regx);
   return found;
}
