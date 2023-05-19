#include <ctest.h>
#include <libproga/stack.h>

CTEST(stack, stack_size)
{
    struct stack* number = stack_create(3);
    stack_push(number, 2);
    stack_push(number, 20);
    int expected = 2;
    int result = stack_size(number);
    ASSERT_EQUAL(expected, result);
    stack_free(number);
}

CTEST(stack, stack_top)
{
    struct stack* number = stack_create(3);
    stack_push(number, 2);
    stack_push(number, 20);
    int expected = 20;
    int result = stack_top(number);
    ASSERT_EQUAL(expected, result);
    stack_free(number);
}

CTEST(stack, stack_push)
{
    struct stack* number = stack_create(5);
    stack_push(number, 2);
    stack_push(number, 20);
    int expected = 0;
    int result = stack_push(number, 100);
    ASSERT_EQUAL(expected, result);

    stack_push(number, 2);
    stack_push(number, 20);
    expected = -1;
    result = stack_push(number, 99);
    ASSERT_EQUAL(expected, result);
    stack_free(number);
}

CTEST(stack, stack_pop)
{
    struct stack* number = stack_create(6);
    stack_push(number, 2);
    stack_push(number, 20);
    int expected = 20;
    int result = stack_pop(number);
    ASSERT_EQUAL(expected, result);

    stack_pop(number);
    expected = -1;
    result = stack_pop(number);
    ASSERT_EQUAL(expected, result);
    stack_free(number);
}