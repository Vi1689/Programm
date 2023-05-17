#include </home/vitaliy/Programm/laba4/include/process.c>
#include </home/vitaliy/Programm/laba4/include/strings.c>
#include "ctest.h"

CTEST(process, process)
{
    char expected[] = "/home/alex/progs/test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc";
    char* result = malloc(sizeof(char) * 300);
    result = process("/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc","+");
    ASSERT_EQUAL(expected, result);
    free(result);
}