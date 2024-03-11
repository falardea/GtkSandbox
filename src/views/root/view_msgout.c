/*
 * Created by french on 3/10/24.
*/
#include "view_msgout.h"
#include "../../globals.h"
#include "../../models/app_model.h"
#include "../../utils/sys_interface.h"

static const char *MSG_OUT_CURSOR_NAME = "msgOutCursor";
static GtkTextMark *msgOutCursor;
static char timestamp[20];  // not sure why it felt better to allocate the memory once

void set_msgout_buffer(const char *msgout)
{
   if (getAppModelInitState() == INIT_SUCCESS)
   {  /* Let's not use the MsgOut widget before it's been built */
      GtkTextBuffer  *tvBuff  =  gtk_text_view_get_buffer(GTK_TEXT_VIEW(g_appWidgetsT->w_tvAppMsgOut));
      GtkTextIter    endIter;
      gtk_text_buffer_get_end_iter(tvBuff, &endIter);

      if (!gtk_text_buffer_get_mark(tvBuff, MSG_OUT_CURSOR_NAME))
      {
         msgOutCursor = gtk_text_mark_new(MSG_OUT_CURSOR_NAME, FALSE);
         gtk_text_buffer_add_mark(tvBuff, msgOutCursor, &endIter);
      }

      gtk_text_buffer_insert(tvBuff, &endIter, msgout, -1);
      gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(g_appWidgetsT->w_tvAppMsgOut), msgOutCursor, 0.0, TRUE, 0.0, 0.0);
   }
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

      logging_llprintf(loglevel, "%s", line_out);
      set_msgout_buffer(ll_msg_out);
   }
}

