#include <libproga/check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i) {
        float value;
        if (check(argv[i], &value)) {
            printf("Ответ: %f\n", value);
        }
    }
}