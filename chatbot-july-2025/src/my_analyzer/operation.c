#include "my_analyzer/my_analyzer.h"

int operation(int type, char *out, size_t size_out, struct data_base *bd,
              struct client *client, char *str) {

  if (out == NULL || bd == NULL || client == NULL || str == NULL) {
    return -1;
  }

  memset(out, '\000', size_out);

  struct expression write = {0};
  struct expression *read = NULL;
  struct parse *root = NULL;

  struct client *tmp = db_get_client(bd, client);
  if (tmp != NULL) {
    client = tmp;
  }

  switch (type) {
  case HELP:
    strcat(out,
           "/help\n/info\n/joke\n/quote\n/joke funny\n/joke not_funny\n/quote "
           "science\n/quote literary\n/joke new funny <text>\n/joke new "
           "not_funny <text>\n/quote new science <text>\n/quote new literary "
           "<text>");
    break;

  case INFO:
    strcat(out, "I am a bot that can perform various commands, for example, I "
                "can make a joke or give a quote.\n"
                "Write \"/help\" to see!\n"
                "They designed it for me.:\n"
                "Afanasyev Nikita\n"
                "Baranov Vitaly\n"
                "Vorman Pavel\n"
                "Teslyuk Alina\n"
                "Curator:\n"
                "Nagel Tatiana");
    break;

  case JOKE:
    srand(time(NULL));
    if ((rand() % 10) & 1) {
      read = db_get_expression(bd, client, FUNNY_JOKES_TYPE);
    } else {
      read = db_get_expression(bd, client, NOT_FUNNY_JOKES_TYPE);
    }
    strcat(out, read->expression);
    break;

  case QUOTE:
    if ((rand() % 10) & 1) {
      read = db_get_expression(bd, client, SCIENTIFIC_QUOTES_TYPE);
    } else {
      read = db_get_expression(bd, client, LITERARY_QUOTES_TYPE);
    }
    strcat(out, read->expression);
    break;

  case FUNNY:
    read = db_get_expression(bd, client, FUNNY_JOKES_TYPE);
    strcat(out, read->expression);
    break;

  case NOT_FUNNY:
    read = db_get_expression(bd, client, NOT_FUNNY_JOKES_TYPE);
    strcat(out, read->expression);
    break;

  case SCIENCE:
    read = db_get_expression(bd, client, SCIENTIFIC_QUOTES_TYPE);
    strcat(out, read->expression);
    break;

  case LIT:
    read = db_get_expression(bd, client, LITERARY_QUOTES_TYPE);
    strcat(out, read->expression);
    break;

  case PUSH_FUNNY:
    write.expression = str;
    write.len = strlen(str);
    write.owner = client;
    if (db_push_expression(bd, &write, FUNNY_JOKES_TYPE)) {
      strcat(out, "The joke wasn't recorded");
    } else {
      strcat(out, "The joke was recorded successfully");
    }
    break;

  case PUSH_NOT_FUNNY:
    write.expression = str;
    write.len = strlen(str);
    write.owner = client;
    if (db_push_expression(bd, &write, NOT_FUNNY_JOKES_TYPE)) {
      strcat(out, "The joke wasn't recorded");
    } else {
      strcat(out, "The joke was recorded successfully");
    }
    break;

  case PUSH_SCIENCE:
    write.expression = str;
    write.len = strlen(str);
    write.owner = client;
    if (db_push_expression(bd, &write, SCIENTIFIC_QUOTES_TYPE)) {
      strcat(out, "The quote was not recorded\n");
    } else {
      strcat(out, "The quote was successfully recorded");
    }
    break;

  case PUSH_LIT:
    write.expression = str;
    write.len = strlen(str);
    write.owner = client;
    if (db_push_expression(bd, &write, LITERARY_QUOTES_TYPE)) {
      strcat(out, "The quote was not recorded\n");
    } else {
      strcat(out, "The quote was successfully recorded");
    }
    break;

  case COME:
    root = create_arr_tok();
    if (root == NULL) {
      ERROR("create_arr_tok");
      return -1;
    }

    if (splitting_into_tokens(str, root) == -1) {
      delete_arr_tok(root);
      return -1;
    }

    if (db_lookup_client(bd, client)) {
      if (!strcmp(client->user_password, root->set_token[1].str)) {
        strcat(out, "true ");
        snprintf(out + 5, 10, "%d", client->message_counter);
      } else {
        strcat(out, "false");
      }
    } else {
      strcat(out, "false");
    }
    delete_arr_tok(root);
    break;

  case REGISTR:
    root = create_arr_tok();
    if (root == NULL) {
      ERROR("create_arr_tok");
      return -1;
    }

    if (splitting_into_tokens(str, root) == -1) {
      delete_arr_tok(root);
      return -1;
    }

    struct client new_client = {0};

    new_client.user_ip_address = client->user_ip_address;
    new_client.user_mac_address = client->user_mac_address;
    new_client.wrong_command_counter = 0;
    new_client.username = root->set_token[0].str;
    new_client.user_password = root->set_token[1].str;

    struct client *tmp = db_get_client(bd, &new_client);
    if (tmp != NULL) {
      strcat(out, "false exist");
    } else {
      if (!db_push_client(bd, &new_client)) {
        strcat(out, "true");
      } else {
        strcat(out, "error bd");
      }
    }
    delete_arr_tok(root);
    break;

  case MISSPELL:
    strcat(out, "misspel");
    break;

  case BAN:
    strcat(out, "BAN");
    break;

  case ERROR:
    if (db_increase_wrong_counter(bd, client) == 0) {
      strcat(out, "+1 error, if there are 3, then you will be banned)))");
      if (client->wrong_command_counter == 3) {
        if (db_ban_client(bd, client)) {
          ERROR("db_ban_client");
          return -1;
        }
      }
    } else {
      ERROR("db_increase_wrong_counter");
      return -1;
    }
    break;

  case UPDATA:
    strcat(out, "yes ");
    snprintf(out + 4, 10, "%d", client->message_counter);
    break;

  default:
    return -1;
  }

  if (type == HELP || type == INFO || type == JOKE || type == QUOTE ||
      type == FUNNY || type == NOT_FUNNY || type == LIT || type == SCIENCE ||
      type == ERROR) {
    if (db_push_message(bd, client, out)) {
      ERROR("db_push_message");
      return -1;
    }
  }

  return 0;
}
