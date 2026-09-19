#include "unity.h"

/*
 * Unity requires these two functions.
 *
 * setUp() runs BEFORE every test.
 * Use it to initialize/reset shared test data.
 */
void setUp(void)
{
}

/*
 * tearDown() runs AFTER every test.
 * Use it to free memory, close files, reset state, etc.
 */
void tearDown(void)
{
}


/* --------------------------------------------------------- */
/* Basic boolean assertions                                  */
/* --------------------------------------------------------- */

void test_boolean_assertions(void)
{
    TEST_ASSERT_TRUE(1);
    TEST_ASSERT_FALSE(0);

    TEST_ASSERT(5 > 2);
}


/* --------------------------------------------------------- */
/* Integer assertions                                        */
/* --------------------------------------------------------- */

void test_integer_assertions(void)
{
    int value = 10;

    TEST_ASSERT_EQUAL_INT(10, value);

    /* Other integer types are also supported */
    TEST_ASSERT_EQUAL_UINT(10u, 10u);
    TEST_ASSERT_EQUAL_INT64(100L, 100L);
}


/* --------------------------------------------------------- */
/* Integer comparison assertions                             */
/* --------------------------------------------------------- */

void test_integer_comparisons(void)
{
    int value = 10;

    TEST_ASSERT_GREATER_THAN(5, value);
    TEST_ASSERT_LESS_THAN(20, value);

    TEST_ASSERT_GREATER_OR_EQUAL(10, value);
    TEST_ASSERT_LESS_OR_EQUAL(10, value);
}


/* --------------------------------------------------------- */
/* Integer range assertions                                  */
/* --------------------------------------------------------- */

void test_integer_within_range(void)
{
    /*
     * Expected value: 100
     * Allowed difference: +/- 5
     *
     * So anything from 95 to 105 passes.
     */
    TEST_ASSERT_INT_WITHIN(5, 100, 103);
}


/* --------------------------------------------------------- */
/* Character assertions                                      */
/* --------------------------------------------------------- */

void test_character_assertions(void)
{
    char ch = 's';

    TEST_ASSERT_EQUAL_CHAR('s', ch);
}


/* --------------------------------------------------------- */
/* String assertions                                         */
/* --------------------------------------------------------- */

void test_string_assertions(void)
{
    const char *name = "seek";

    TEST_ASSERT_EQUAL_STRING("seek", name);

    /*
     * Compare only the first N characters.
     */
    TEST_ASSERT_EQUAL_STRING_LEN("seeker", "seek", 4);
}


/* --------------------------------------------------------- */
/* Pointer assertions                                        */
/* --------------------------------------------------------- */

void test_pointer_assertions(void)
{
    int value = 42;

    int *ptr = &value;
    int *null_ptr = NULL;

    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_NULL(null_ptr);

    /*
     * Check that two pointers point to the same address.
     */
    TEST_ASSERT_EQUAL_PTR(&value, ptr);
}


/* --------------------------------------------------------- */
/* Array assertions                                          */
/* --------------------------------------------------------- */

void test_array_assertions(void)
{
    int expected[] = {1, 2, 3, 4};
    int actual[]   = {1, 2, 3, 4};

    /*
     * Compare 4 integer elements.
     */
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 4);
}


/* --------------------------------------------------------- */
/* Memory assertions                                         */
/* --------------------------------------------------------- */

void test_memory_assertions(void)
{
    unsigned char expected[] = {0x01, 0x02, 0x03};
    unsigned char actual[]   = {0x01, 0x02, 0x03};

    /*
     * Compare raw memory byte-for-byte.
     *
     * This can be useful later for structs, buffers,
     * binary data, file headers, etc.
     */
    TEST_ASSERT_EQUAL_MEMORY(expected, actual, sizeof(expected));
}


/* --------------------------------------------------------- */
/* Floating-point assertions                                 */
/* --------------------------------------------------------- */

void test_float_assertions(void)
{
    float value = 3.14f;

    /*
     * Unity handles floating-point comparisons with
     * an appropriate tolerance.
     */
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 3.14f, value);
}


/* --------------------------------------------------------- */
/* Assertions with custom messages                           */
/* --------------------------------------------------------- */

void test_assertion_with_message(void)
{
    int result = 4;

    TEST_ASSERT_EQUAL_INT_MESSAGE(
        4,
        result,
        "2 + 2 should equal 4"
    );
}


/* --------------------------------------------------------- */
/* Explicit pass                                             */
/* --------------------------------------------------------- */

void test_explicit_pass(void)
{
    /*
     * Immediately marks this test as passed.
     */
    TEST_PASS();
}


/* --------------------------------------------------------- */
/* Ignored / skipped test                                    */
/* --------------------------------------------------------- */

void test_not_implemented_yet(void)
{
    /*
     * Useful when you want to commit a test placeholder
     * before the feature has been implemented.
     */
    TEST_IGNORE_MESSAGE("Feature not implemented yet");
}


/* --------------------------------------------------------- */
/* Test runner                                               */
/* --------------------------------------------------------- */

int main(void)
{
    /*
     * Start Unity's test framework.
     */
    UNITY_BEGIN();

    /*
     * Every test function must be registered with RUN_TEST().
     */
    RUN_TEST(test_boolean_assertions);
    RUN_TEST(test_integer_assertions);
    RUN_TEST(test_integer_comparisons);
    RUN_TEST(test_integer_within_range);
    RUN_TEST(test_character_assertions);
    RUN_TEST(test_string_assertions);
    RUN_TEST(test_pointer_assertions);
    RUN_TEST(test_array_assertions);
    RUN_TEST(test_memory_assertions);
    RUN_TEST(test_float_assertions);
    RUN_TEST(test_assertion_with_message);
    RUN_TEST(test_explicit_pass);
    RUN_TEST(test_not_implemented_yet);

    /*
     * Prints the final test summary and returns
     * a non-zero exit status if any test failed.
     *
     * That makes it work nicely with:
     *
     *     make test
     *
     * and later with CI systems like GitHub Actions.
     */
    return UNITY_END();
}
