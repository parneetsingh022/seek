#include "unity.h"
#include <seek/path.h>

void setUp(void)
{
}

void tearDown(void)
{
}


/* --------------------------------------------------------- */
/* path_is_abs() tests                                       */
/* --------------------------------------------------------- */

void test_path_is_abs_with_root(void)
{
    TEST_ASSERT_TRUE(path_is_abs("/"));
}

void test_path_is_abs_with_absolute_path(void)
{
    TEST_ASSERT_TRUE(path_is_abs("/home/user/file.txt"));
}

void test_path_is_abs_with_relative_path(void)
{
    TEST_ASSERT_FALSE(path_is_abs("src/main.c"));
}

void test_path_is_abs_with_current_directory_path(void)
{
    TEST_ASSERT_FALSE(path_is_abs("./src/main.c"));
}

void test_path_is_abs_with_parent_directory_path(void)
{
    TEST_ASSERT_FALSE(path_is_abs("../src/main.c"));
}

void test_path_is_abs_with_filename_only(void)
{
    TEST_ASSERT_FALSE(path_is_abs("main.c"));
}

void test_path_is_abs_with_empty_string(void)
{
    TEST_ASSERT_FALSE(path_is_abs(""));
}

/* --------------------------------------------------------- */
/* Test runner                                               */
/* --------------------------------------------------------- */

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_path_is_abs_with_root);
    RUN_TEST(test_path_is_abs_with_absolute_path);
    RUN_TEST(test_path_is_abs_with_relative_path);
    RUN_TEST(test_path_is_abs_with_current_directory_path);
    RUN_TEST(test_path_is_abs_with_parent_directory_path);
    RUN_TEST(test_path_is_abs_with_filename_only);
    RUN_TEST(test_path_is_abs_with_empty_string);

    return UNITY_END();
}
