#include "calc.h"
#include "stack.h"

int calc(struct stack* number, struct stack* op)
{
    float a = stack_pop(number), b = stack_pop(number);
    int c = stack_pop(op);
    switch (c) {
    case 43:
        if (stack_push(number, b + a)) {
            return 1;
        }
        break;
    case 45:
        if (stack_push(number, b - a)) {
            return 1;
        }
        break;
    case 42:
        if (stack_push(number, b * a)) {
            return 1;
        }
        break;
    case 47:
        if (!a) {
            return 1;
        }
        if (stack_push(number, b / a)) {
            return 1;
        }
        break;
    }
    return 0;
}

int priority(int a)
{
    if (a == 43 || a == 45) {
        return 1;
    }
    if (a == 42 || a == 47) {
        return 2;
    }
    return 0;
}