#include "calc.h"
#include "check.h"
#include "stack.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    float value;
    if (check(argv[1], &value)) {
        printf("Ответ: %f\n", value);
    } else {
        printf("Неправильно введено выражение\n");
    }
}