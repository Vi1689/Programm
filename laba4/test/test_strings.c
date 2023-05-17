#include </home/vitaliy/Programm/laba4/include/strings.c>
#include "ctest.h"
#include <stdlib.h>
#include <stdio.h>

CTEST(strings, slen)
{
    int expected = 5;
    int result = slen("12345");
    ASSERT_EQUAL(expected, result);
}

CTEST(strings, sspn)
{
    int expected = 0;
    char sym[] = {'\\', ':', '*', '?', '"', '<', '>', '|'};
    int result = sspn("12345", sym);
    ASSERT_EQUAL(expected, result);

    expected = 1;
    result = sspn("1:2345", sym);
    ASSERT_EQUAL(expected, result);
}

CTEST(strings, scmp)
{
    int expected = -1;
    int result = scmp("abcd", "abdc");
    ASSERT_EQUAL(expected, result);

    expected = 1;
    result = scmp("abdc", "abcd");
    ASSERT_EQUAL(expected, result);

    expected = 0;
    result = scmp("abdc", "abdc");
    ASSERT_EQUAL(expected, result);
}
/*
CTEST(strings, scpy) {
    char expected1[] = "0123456789";
    char* result1 = malloc(sizeof(char) * 20);
    result1 = scpy(result1, expected1, 10);
    ASSERT_STR(expected1, result1);
    free(result1);
}

CTEST(strings, erase)
{
    char expected[] = "relt";
    char* result = malloc(sizeof(char) * 20);
    result = erase("result", 3, 5);
    ASSERT_STR(expected, result);
    free(result);
}

CTEST(strings, copy_m)
{
    char expected[] = "0123456789";
    char* result = malloc(sizeof(char) * 20);
    result = copy_m(result, expected, 0, 0);
    ASSERT_STR(expected, result);
    free(result);
}
*/