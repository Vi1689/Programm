#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <libproga/check.h>

CTEST(check, check){
    char* str = "(2/0)";
    float value;
    check(str, &value);

    str = "2-2+()";
    check(str, &value);

    str = "3*)3";
    check(str, &value);

    str = "2/a";
    check(str, &value);

    str = "2/(2";
    check(str, &value);

    str = "2//";
    check(str, &value);

    str = "((2+1)/12))";
    check(str, &value);

    str = "(2.2/2.2.2)";
    check(str, &value);
}
