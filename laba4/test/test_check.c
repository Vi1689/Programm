#include </home/vitaliy/Programm/laba4/include/check.c>
#include </home/vitaliy/Programm/laba4/include/strings.c>
#include "ctest.h"

CTEST(check, check)
{
    int expected = 0;
    int result = check("~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+", "/home/stud");
    ASSERT_EQUAL(expected, result);

     expected = 1;
     result = check("~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "aa", "/home/stud");
    ASSERT_EQUAL(expected, result);

     expected = 2;
     result = check("~/games/packman.cpp+~<>alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+", "/home/stud");
    ASSERT_EQUAL(expected, result);

     expected = 3;
     result = check("~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+", "/home/stud");
    ASSERT_EQUAL(expected, result);

     expected = 4;
     result = check("~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+usr/bin/gcc", "+", "/home/stud");
    ASSERT_EQUAL(expected, result);

    expected = 5;
     result = check("~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc", "+", "/home<stud");
    ASSERT_EQUAL(expected, result);
}