#include "ctest.h"
#include <libproga/calc.h>
#include <libproga/stack.h>

CTEST(calc, calc)
{
    struct stack* number = stack_create(2);
    struct stack* op = stack_create(1);
    stack_push(number, 2);
    stack_push(number, 2);
    stack_push(op, 43);
    int expected = 4;
    int result = calc(number, op);
    ASSERT_EQUAL(expected, result);

    stack_push(number, 2);
    stack_push(number, 2);
    stack_push(op, 45);
    expected = 0;
    result = calc(number, op);
    ASSERT_EQUAL(expected, result);

    stack_push(number, 3);
    stack_push(number, 3);
    stack_push(op, 42);
    expected = 9;
    result = calc(number, op);
    ASSERT_EQUAL(expected, result);

    stack_push(number, 2);
    stack_push(number, 2);
    stack_push(op, 47);
    expected = 1;
    result = calc(number, op);
    ASSERT_EQUAL(expected, result);
    stack_free(number);
    stack_free(op);
}

CTEST(calc, priority){
    int expected = 1;
    int result = priority(43);
    ASSERT_EQUAL(expected, result);

    expected = 1;
    result = priority(45);
    ASSERT_EQUAL(expected, result);

    expected = 2;
    result = priority(42);
    ASSERT_EQUAL(expected, result);

    expected = 2;
    result = priority(47);
    ASSERT_EQUAL(expected, result);

    expected = 0;
    result = priority(40);
    ASSERT_EQUAL(expected, result);
}