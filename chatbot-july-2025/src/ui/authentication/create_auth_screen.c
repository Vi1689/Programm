#include <ui/ui_auth.h>

int create_auth_screen(char *title, char *login, char *password) {

  extern char cur_screen[];
  extern struct client_message *credentials;
  int win_h, win_w;
  WINDOW *win = create_window(LINES - 4, COLS - 10, &win_h, &win_w);
  if (win == NULL) {
    return -1;
  }
  strcpy(cur_screen, title);

  int mid_y = win_h / 2;
  int login_y = mid_y - 1;
  int pass_y = mid_y + 1;
  int lbl_w = strlen("Login: ");
  int start_x = (win_w - (lbl_w + FIELD_WIDTH)) / 2;

  FIELD **fields = create_fields(login_y, pass_y, start_x, lbl_w);
  if (fields == NULL) {
    delwin(win);
    return -1;
  }

  FORM *form = new_form(fields);
  if (form == NULL) {
    free_field(fields[0]);
    free_field(fields[1]);
    free(fields);
    delwin(win);
    return -1;
  }
  set_form_win(form, win);
  set_form_sub(form, derwin(win, win_h - 6, win_w - 4, 1, 1));
  post_form(form);

  draw_labels(win, login_y, pass_y, start_x);
  draw_title_and_instructions(win, title, win_h, win_w);
  form_driver(form, REQ_FIRST_FIELD);

  bool quit = false;
  handle_auth_input(win, form, fields, login, password, &quit);

  if (strcmp(title, "Registration") == 0) {
    snprintf(credentials->message, 512, "/login new %s /password new %s", login,
             password);
  } else if (strcmp(title, "Authorization") == 0) {
    snprintf(credentials->message, 512, "/login %s /password %s", login,
             password);
  }
  snprintf(credentials->user_login, 32, "%s", login);
  unpost_form(form);
  free_form(form);
  free_field(fields[0]);
  free_field(fields[1]);
  free(fields);
  delwin(win);

  return 0;
}