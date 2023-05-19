#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <libproga/check.h>

CTEST(check, check){
    char* str = "2/0";
    float value;
    check(str, &value);

    char* str1;
    str1 = "2-2+()";
    value = 0;
    check(str1, &value);

    char* str2;
    str2 = "3*)3";
    value = 0;
    check(str2, &value);

    char* str3;
    str3 = "2/a";
    check(str3, &value);
}
