#include <ui/ui_auth.h>

FIELD **create_fields(int login_y, int pass_y, int start_x, int lbl_w) {

  FIELD **fields = calloc(FIELD_COUNT + 1, sizeof(FIELD *));
  fields[0] = new_field(1, FIELD_WIDTH, login_y, start_x + lbl_w, 0, 0);
  fields[1] = new_field(1, FIELD_WIDTH, pass_y, start_x + lbl_w, 0, 0);

  for (int i = 0; i < FIELD_COUNT; i++) {
    set_field_back(fields[i], COLOR_PAIR(2));
    field_opts_off(fields[i], O_AUTOSKIP);
    field_opts_off(fields[i], O_STATIC);
    field_opts_on(fields[i], O_EDIT);
    set_field_type(fields[i], TYPE_ALNUM, 1);
  }

  return fields;
}