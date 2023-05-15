#include "stack.h"

int main()
{
    char* str = malloc(sizeof(char) * 100);
    char* s = malloc(sizeof(char) * 100);
    fgets(str, 100, stdin);
    fflush(stdin);
    struct stack* num = stack_create(100);
    struct stack_char* ops = stack_create_char(100);
    int k = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == '1' || str[i] == '2' || str[i] == '3' || str[i] == '4'
            || str[i] == '5' || str[i] == '6' || str[i] == '7' || str[i] == '8'
            || str[i] == '9' || str[i] == '0' || str[i] == '.') {
            s[k++] = str[i];
        } else if (str[i] != ' ') {
            stack_push(num, atof(s));
            memset(s, 0, k);
            k = 0;
        }
        if (str[i] == '-' || str[i] == '+' || str[i] == '/' || str[i] == '*'
            || str[i] == '(' || str[i] == ')') {
            if (((ops->a[stack_size_char(ops) - 1] == '*'
                  || ops->a[stack_size_char(ops) - 1] == '/')
                 && (str[i] == '+' || str[i] == '-'))) {
                float y = stack_pop(num), x = stack_pop(num);
                int op = stack_pop_char(ops);
                if (op == 43) {
                    x = x + y;
                }
                if (op == 42) {
                    x = x * y;
                }
                if (op == 47) {
                    x = x / y;
                }
                if (op == 45) {
                    x = x - y;
                }
                stack_push(num, x);
            }
            stack_push_char(ops, str[i]);
        }
    }
    for (int i = 0; i < stack_size_char(ops) + 1; ++i) {
        float y = stack_pop(num), x = stack_pop(num);
        // printf("x = %f y = %f ", x, y);
        int op = stack_pop_char(ops);
        if (op == 43) {
            x = x + y;
            // printf("+\n%f", x);
        }
        if (op == 42) {
            x = x * y;
            // printf("*\n%f", x);
        }
        if (op == 47) {
            x = x / y;
            // printf("/\n%f", x);
        }
        if (op == 45) {
            x = x - y;
            // printf("-\n%f", x);
        }
        stack_push(num, x);
    }
    printf("Ответ = %f\n", stack_pop(num));
    stack_free(num);
    stack_free_char(ops);
    free(str);
    free(s);
}