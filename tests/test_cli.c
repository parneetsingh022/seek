#include "unity.h"

#include <seek/cli.h>

void setUp(void) {}

void tearDown(void) {}

void test_cli_parse_valid_target(void)
{
	struct cli_options options = {0};
	char *argv[] = {"seek", "hello"};

	cli_parse(&options, 2, argv);

	TEST_ASSERT_EQUAL_STRING("hello", options.target);
}

void test_cli_parse_default_path(void)
{
	struct cli_options options = {0};
	char *argv[] = {"seek", "hello"};

	cli_parse(&options, 2, argv);

	TEST_ASSERT_EQUAL_STRING(".", options.path);
}

void test_cli_parse_target_with_spaces(void)
{
	struct cli_options options = {0};
	char *argv[] = {"seek", "hello world"};

	cli_parse(&options, 2, argv);

	TEST_ASSERT_EQUAL_STRING("hello world", options.target);
}

void test_cli_parse_target_pointer(void)
{
	struct cli_options options = {0};
	char *argv[] = {"seek", "hello"};

	cli_parse(&options, 2, argv);

	TEST_ASSERT_EQUAL_PTR(argv[1], options.target);
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_cli_parse_valid_target);
	RUN_TEST(test_cli_parse_default_path);
	RUN_TEST(test_cli_parse_target_with_spaces);
	RUN_TEST(test_cli_parse_target_pointer);

	return UNITY_END();
}
