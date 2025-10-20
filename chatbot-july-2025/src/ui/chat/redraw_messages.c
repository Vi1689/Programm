#include <ui/ui_chat.h>

void redraw_messages(ChatContext *chat_context) {

  extern WINDOW *pad_chat;
  extern char common_login[32];
  werase(pad_chat);
  int y = 1;

  for (int i = 0; i < chat_context->msg_count; i++) {
    int width = getmaxx(pad_chat);
    int box_width = strlen(chat_context->messages[i].text) + 4;

    if (box_width > MSG_WIDTH) {
      box_width = MSG_WIDTH;
    }
    if ((size_t)box_width - 4 < strlen(common_login)) {
      box_width = strlen(common_login) + 4;
    }

    int x;

    if (chat_context->messages[i].from_bot) {
      x = 2;
    } else {
      x = width - box_width - 2;
      if (x < 2) {
        x = 2;
      }
    }

    int box_h = draw_message_box(pad_chat, y, x, chat_context->messages[i].text,
                                 chat_context->messages[i].from_bot);
    y += box_h + 1;
  }

  int max_y = getmaxy(stdscr);
  int chat_h = max_y - INPUT_H - 2;

  int prev_pad_pos = chat_context->pad_pos;
  int full_height = y;
  int new_pad_pos = full_height - chat_h;

  if (new_pad_pos < 0)
    new_pad_pos = 0;

  if (prev_pad_pos >= chat_context->max_pos) {
    chat_context->pad_pos = new_pad_pos;
  }

  chat_context->max_pos = new_pad_pos;

  refresh_pad(&chat_context->pad_pos);
}