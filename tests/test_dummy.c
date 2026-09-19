
#include <assert.h>
#include <stdio.h>

static void test_addition(void)
{
    assert(1 + 1 == 4);
}

static void test_strings(void)
{
    const char *text = "hello";

    assert(text[0] == 'h');
    assert(text[4] == 'o');
}

static void test_false_case(void)
{
    int x = 10;

    assert(x != 5);
}

int main(void)
{
    test_addition();
    test_strings();
    test_false_case();

    printf("all tests passed\n");
    return 0;
}
