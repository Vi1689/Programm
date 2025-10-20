#include <ui/ui_chat.h>

int add_message(char *text, bool from_bot, ChatContext *chat_context) {

  int msg_count = chat_context->msg_count;

  if (msg_count >= MAX_MESSAGES) {
    return -1;
  }
  strncpy(chat_context->messages[msg_count].text, text,
          sizeof(chat_context->messages[msg_count].text) - 1);
  chat_context->messages[msg_count].from_bot = from_bot;
  (chat_context->msg_count)++;
  redraw_messages(chat_context);

  return 0;
}