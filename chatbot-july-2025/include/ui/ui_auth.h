#pragma once

#include "ui.h"
#include <form.h>
#include <ncurses.h>

#define FIELD_WIDTH 32
#define FIELD_COUNT 2

/**
 * @brief Создает экран авторизации или регистрации.
 * @param title Заголовок экрана.
 * @param login Указатель на буфер для логина.
 * @param password Указатель на буфер для пароля.
 * @return Код завершения: 0 в случае успеха, иначе ненулевое значение.
 */
int create_auth_screen(char *title, char *login, char *password);

/**
 * @brief Создает поля ввода для формы авторизации.
 * @param login_y Координата Y для поля логина.
 * @param pass_y Координата Y для поля пароля.
 * @param start_x Начальная координата X.
 * @param lbl_w Ширина меток полей.
 * @return Указатель на массив полей формы.
 */
FIELD **create_fields(int login_y, int pass_y, int start_x, int lbl_w);

/**
 * @brief Создает и настраивает окно для экрана авторизации.
 * @param height Высота окна.
 * @param width Ширина окна.
 * @param win_h Указатель для сохранения высоты окна.
 * @param win_w Указатель для сохранения ширины окна.
 * @return Указатель на созданное окно.
 */
WINDOW *create_window(int height, int width, int *win_h, int *win_w);

/**
 * @brief Рисует поля логина и пароля.
 * @param win Указатель на окно.
 * @param login_y Координата Y для поля логина.
 * @param pass_y Координата Y для поля пароля.
 * @param start_x Начальная координата X.
 */
void draw_labels(WINDOW *win, int login_y, int pass_y, int start_x);

/**
 * @brief Рисует заголовок и инструкции на экране авторизации.
 * @param win Указатель на окно.
 * @param title Заголовок экрана.
 * @param win_h Высота окна.
 * @param win_w Ширина окна.
 */
void draw_title_and_instructions(WINDOW *win, const char *title, int win_h,
                                 int win_w);

/**
 * @brief Обрабатывает ввод пользователя на экране авторизации.
 * @param win Указатель на окно.
 * @param form Указатель на форму.
 * @param fields Указатель на массив полей формы.
 * @param login Указатель на буфер для логина.
 * @param password Указатель на буфер для пароля.
 * @param quit_flag Указатель на флаг выхода.
 */
void handle_auth_input(WINDOW *win, FORM *form, FIELD **fields, char *login,
                       char *password, bool *quit_flag);

/**
 * @brief Инициализирует цветовые пары для экрана авторизации.
 */
void init_colors_auth(void);