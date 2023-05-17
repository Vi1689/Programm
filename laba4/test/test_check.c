#include </home/vitaliy/Programm/laba4/include/check.c>
#include </home/vitaliy/Programm/laba4/include/strings.c>
#include "ctest.h"

CTEST(check, check)
{
    int expected = 0;
    int result = check("/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+");
    ASSERT_EQUAL(expected, result);

     expected = 1;
     result = check("/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "aa");
    ASSERT_EQUAL(expected, result);

     expected = 2;
     result = check("/home/alex/video/../<>progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+");
    ASSERT_EQUAL(expected, result);

     expected = 3;
     result = check("/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+");
    ASSERT_EQUAL(expected, result);

     expected = 4;
     result = check("/home/alex/video/../progs/./test.c+~alex/docs+~/study/Prog/lab4.c+usr/bin/gcc", "+");
    ASSERT_EQUAL(expected, result);
}