#include "check.h"
#include "calc.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* check(char* new_str, float* value)
{
    char* str = malloc(sizeof(char) * strlen(new_str));
    for (int i = 0, k = 0; i < strlen(new_str); ++i) {
        if (new_str[i] != ' ') {
            str[k++] = new_str[i];
        }
    }
    struct stack* number = stack_create(50);
    struct stack* op = stack_create(50);
    char* numder_char = malloc(sizeof(char) * 10);
    int k = 0, flag = 0, flag_sk = 0, flag_t = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '(') {
            flag++;
        }
        if (str[i] == ')') {
            flag_sk++;
        }
        if (str[i] == '(' && str[i + 1] == ')') {
            printf("Скобки не должины быть пустыми\n");
            return NULL;
        }
        if (flag < flag_sk) {
            printf("Неправильное расположение скобок\n");
            return NULL;
        }
        if (str[i] == '(' && str[i + 2] == ')'
            && (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*'
                || str[i + 1] == '/')) {
            printf("Неправильное расположение знака\n");
            return NULL;
        }
    }
    if (flag != flag_sk) {
        printf("Недостаточно скобок\n");
        return NULL;
    }
    flag = 1;
    flag_sk = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (flag_t > 1) {
            printf("Неправильно написано вещественное число\n");
            return NULL;
        }
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '.' && !flag_t
            || str[i] == '-' && flag) {
            numder_char[k++] = str[i];
            flag = 0;
            if (str[i] == '.') {
                flag_t++;
            }
        } else if (
                str[i] == '+' || str[i] == '-' && !flag || str[i] == '/'
                || str[i] == '*') {
            if (str[i + 1] == '+' || str[i + 1] == '-' && !flag
                || str[i + 1] == '/' || str[i + 1] == '*'
                || str[i + 1] == '\0') {
                printf("Неправильное расположение знака\n");
                return NULL;
            }
            if (!stack_size(op)) {
                if (!flag_sk) {
                    if (stack_push(number, atof(numder_char))) {
                        return NULL;
                    }
                }
                k = 0;
                memset(numder_char, '\0', sizeof(char) * strlen(numder_char));
                if (stack_push(op, str[i])) {
                    return NULL;
                }
            } else if (stack_size(op) && rang(str[i]) > rang(stack_top(op))) {
                if (!flag_sk) {
                    if (stack_push(number, atof(numder_char))) {
                        return NULL;
                    }
                }
                k = 0;
                memset(numder_char, '\0', sizeof(char) * strlen(numder_char));
                if (stack_push(op, str[i])) {
                    return NULL;
                }
            } else if (stack_size(op) && rang(str[i]) <= rang(stack_top(op))) {
                if (!flag_sk) {
                    if (stack_push(number, atof(numder_char))) {
                        return NULL;
                    }
                }
                k = 0;
                memset(numder_char, '\0', sizeof(char) * strlen(numder_char));
                if (calc(number, op)) {
                    printf("На ноль нельзя делить\n");
                    return NULL;
                }
                if (stack_push(op, str[i])) {
                    return NULL;
                }
            }
            flag = 1;
            flag_sk = 0;
            flag_t = 0;
        } else if (str[i] == '(') {
            if (stack_push(op, str[i])) {
                return NULL;
            }
            flag_t = 0;
        } else if (str[i] == ')') {
            if (!flag_sk) {
                if (stack_push(number, atof(numder_char))) {
                    return NULL;
                }
            }
            k = 0;
            memset(numder_char, '\0', sizeof(char) * strlen(numder_char));
            while (stack_top(op) != 40) {
                if (calc(number, op)) {
                    printf("На ноль нельзя делить\n");
                    return NULL;
                }
            }
            stack_pop(op);
            flag_sk = 1;
            flag_t = 0;
        } else {
            printf("Неправильный символ\n");
            return NULL;
        }
    }
    if (!flag_sk) {
        if (stack_push(number, atof(numder_char))) {
            return NULL;
        }
    }
    k = 0;
    memset(numder_char, '\0', sizeof(char) * strlen(numder_char));
    while (stack_size(op)) {
        if (calc(number, op)) {
            printf("На ноль нельзя делить\n");
            return NULL;
        }
    }
    *value = stack_top(number);
    stack_free(number);
    stack_free(op);
    free(str);
    return value;
}