#include "check.h"
#include "calc.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* check(char* str, float* value)
{
    struct stack* number = stack_create(50);
    struct stack* op = stack_create(50);
    char* numder_char = malloc(sizeof(char) * 10);
    int k = 0, flag = 0, flag_sk = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '(') {
            flag++;
        }
        if (str[i] == ')') {
            flag_sk++;
        }
    }
    if (flag != flag_sk) {
        return NULL;
    }
    flag = 1;
    flag_sk = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == ' ') {
            continue;
        }
        if (str[i] >= '0' && str[i] <= '9' || str[i] == '.'
            || str[i] == '-' && flag) {
            numder_char[k++] = str[i];
            flag = 0;
        } else if (
                str[i] == '+' || str[i] == '-' && !flag || str[i] == '/'
                || str[i] == '*') {
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
                    return NULL;
                }
                if (stack_push(op, str[i])) {
                    return NULL;
                }
            }
            flag = 1;
            flag_sk = 0;
        } else if (str[i] == '(') {
            if (stack_push(op, str[i])) {
                return NULL;
            }
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
                    return NULL;
                }
            }
            stack_pop(op);
            flag_sk = 1;
        } else {
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
            return NULL;
        }
    }
    *value = stack_top(number);
    stack_free(number);
    stack_free(op);
    return value;
}