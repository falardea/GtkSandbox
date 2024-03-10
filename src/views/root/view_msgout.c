/*
 * Created by french on 3/10/24.
*/
#include "view_msgout.h"
#include "../../globals.h"
#include "../../models/app_model.h"
#include "../../utils/sys_interface.h"

static char timestamp[20];  // not sure why it felt better to allocate the memory once

void set_msgout_buffer(const char *msgout)
{
   GtkTextBuffer  *tvBuff  =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_appWidgetsT->w_tvAppMsgOut));
   GtkTextIter    endIter;
   gtk_text_buffer_get_end_iter(tvBuff, &endIter);
   gtk_text_buffer_insert(tvBuff, &endIter, msgout, -1);
}

void printLoglevelMsgOut(LOGLEVEL_T loglevel, const char *_format, ...)
{
   if (loglevel >= getAppModelLoglevel()) {
      char ll_msg_out[LOGGING_MAX_MSG_LENGTH + sizeof(timestamp) + (2*sizeof(':')) + sizeof(strLoglevel(loglevel))];
      char line_out[LOGGING_MAX_MSG_LENGTH];
      va_list arg;
      va_start(arg, _format);
      vsnprintf(line_out, sizeof (line_out), _format, arg);
      va_end(arg);

      getTimestamp(timestamp, sizeof(timestamp));
      snprintf(ll_msg_out, sizeof (ll_msg_out), "%s:%s:%s", timestamp, strLoglevel(loglevel), line_out);

      set_msgout_buffer(ll_msg_out);
      logging_llprint(loglevel, "%s", line_out);
   }
}

