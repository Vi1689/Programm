#include <string.h>
#include <ui/ui_auth.h>

void handle_auth_input(WINDOW *win, FORM *form, FIELD **fields, char *login,
                       char *password, bool *quit_flag) {

  int ch;
  bool quit = false;
  extern char cur_screen[];

  int cur_pos_login = 0;
  int max_pos_login = 0;
  int cur_pos_pass = 0;
  int max_pos_pass = 0;
  int is_login = 1;

  form_driver(form, REQ_FIRST_FIELD);
  form_driver(form, REQ_INS_MODE);

  while (!quit && (ch = wgetch(win)) != KEY_F(1)) {
    switch (ch) {
    case KEY_DOWN:
    case '\t':
      form_driver(form, REQ_NEXT_FIELD);
      is_login = 0;
      cur_pos_pass = 0;
      break;

    case KEY_UP:
      form_driver(form, REQ_PREV_FIELD);
      is_login = 1;
      cur_pos_login = 0;
      break;

    case KEY_BACKSPACE:
    case 127:
      if (is_login && cur_pos_login != max_pos_login) {
        if (cur_pos_login != 0) {
          form_driver(form, REQ_LEFT_CHAR);
          cur_pos_login--;
        }
        form_driver(form, REQ_DEL_CHAR);
        max_pos_login--;
      } else if (!is_login && cur_pos_pass != max_pos_pass) {
        if (cur_pos_pass != 0) {
          form_driver(form, REQ_LEFT_CHAR);
          cur_pos_pass--;
        }
        form_driver(form, REQ_DEL_CHAR);
        max_pos_pass--;
      }
      break;

    case KEY_LEFT:
      if (is_login && cur_pos_login > 0) {
        form_driver(form, REQ_LEFT_CHAR);
        cur_pos_login--;
      } else if (!is_login && cur_pos_pass > 0) {
        form_driver(form, REQ_LEFT_CHAR);
        cur_pos_pass--;
      }
      break;

    case KEY_RIGHT:
      if (is_login && cur_pos_login < max_pos_login) {
        form_driver(form, REQ_RIGHT_CHAR);
        cur_pos_login++;
      } else if (!is_login && cur_pos_pass < max_pos_pass) {
        form_driver(form, REQ_RIGHT_CHAR);
        cur_pos_pass++;
      }
      break;

    case KEY_F(2):
      if (strcmp("Registration", cur_screen) == 0) {
        create_auth_screen("Authorization", login, password);
      } else {
        create_auth_screen("Registration", login, password);
      }
      return;

    case KEY_F(3):
      quit = true;
      break;

    default:

      if (cur_pos_login < FIELD_WIDTH && is_login) {
        form_driver(form, ch);
        cur_pos_login++;
        if (cur_pos_login > max_pos_login) {
          max_pos_login = cur_pos_login;
        }
      } else if (cur_pos_pass < FIELD_WIDTH && !is_login) {
        form_driver(form, ch);
        cur_pos_pass++;
        if (cur_pos_pass > max_pos_pass) {
          max_pos_pass = cur_pos_pass;
        }
      }
      break;
    }
    wrefresh(win);
  }

  *quit_flag = quit;

  if (!quit) {
    form_driver(form, REQ_VALIDATION);
    char *raw_login = field_buffer(fields[0], 0);
    char *raw_password = field_buffer(fields[1], 0);

    strncpy(login, raw_login, FIELD_WIDTH);
    strncpy(password, raw_password, FIELD_WIDTH);
    login[strcspn(login, " ")] = '\0';
    password[strcspn(password, " ")] = '\0';
  }
}