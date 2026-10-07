#include "unity.h"

#include <seek/cli.h>

enum {
	FLAG_RECURSIVE = 1 << 0,
	FLAG_HIDDEN = 1 << 1,
	FLAG_VERBOSE = 1 << 2,
};

void setUp(void) {}

void tearDown(void) {}



void test_cli_init_sets_target(void)
{
	struct cli_args args;

	cli_init(&args, "needle", "/tmp");

	TEST_ASSERT_EQUAL_STRING("needle", args.target);
}

void test_cli_init_sets_path(void)
{
	struct cli_args args;

	cli_init(&args, "needle", "/tmp/search");

	TEST_ASSERT_EQUAL_STRING("/tmp/search", args.path);
}

void test_cli_init_clears_flags(void)
{
	struct cli_args args = {
		.flags = FLAG_RECURSIVE | FLAG_HIDDEN,
	};

	cli_init(&args, "needle", "/tmp");

	TEST_ASSERT_EQUAL_INT(0, args.flags);
}

void test_cli_init_sets_all_fields(void)
{
	struct cli_args args;

	cli_init(&args, "needle", "/tmp/search");

	TEST_ASSERT_EQUAL_STRING("needle", args.target);
	TEST_ASSERT_EQUAL_STRING("/tmp/search", args.path);
	TEST_ASSERT_EQUAL_INT(0, args.flags);
}

void test_cli_init_overwrites_existing_values(void)
{
	struct cli_args args = {
		.target = "old",
		.path = "/old/path",
		.flags = FLAG_RECURSIVE,
	};

	cli_init(&args, "new", "/new/path");

	TEST_ASSERT_EQUAL_STRING("new", args.target);
	TEST_ASSERT_EQUAL_STRING("/new/path", args.path);
	TEST_ASSERT_EQUAL_INT(0, args.flags);
}

void test_cli_init_accepts_empty_target(void)
{
	struct cli_args args;

	cli_init(&args, "", "/tmp");

	TEST_ASSERT_EQUAL_STRING("", args.target);
}

void test_cli_init_accepts_empty_path(void)
{
	struct cli_args args;

	cli_init(&args, "needle", "");

	TEST_ASSERT_EQUAL_STRING("", args.path);
}

void test_cli_add_flags_sets_flag(void)
{
	struct cli_args args = {0};

	cli_add_flags(&args, FLAG_RECURSIVE);

	TEST_ASSERT_EQUAL_INT(FLAG_RECURSIVE, args.flags);
}

void test_cli_add_flags_preserves_existing_flags(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE,
	};

	cli_add_flags(&args, FLAG_HIDDEN);

	TEST_ASSERT_EQUAL_INT(FLAG_RECURSIVE | FLAG_HIDDEN, args.flags);
}

void test_cli_remove_flags_clears_flag(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE | FLAG_HIDDEN,
	};

	cli_remove_flags(&args, FLAG_RECURSIVE);

	TEST_ASSERT_EQUAL_INT(FLAG_HIDDEN, args.flags);
}

void test_cli_remove_flags_preserves_other_flags(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE | FLAG_HIDDEN,
	};

	cli_remove_flags(&args, FLAG_RECURSIVE);

	TEST_ASSERT_FALSE(args.flags & FLAG_RECURSIVE);
	TEST_ASSERT_TRUE(args.flags & FLAG_HIDDEN);
}

void test_cli_has_flags_returns_true_when_all_flags_are_set(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE | FLAG_HIDDEN,
	};

	TEST_ASSERT_TRUE(cli_has_flags(&args, FLAG_RECURSIVE));
	TEST_ASSERT_TRUE(cli_has_flags(&args, FLAG_HIDDEN));
	TEST_ASSERT_TRUE(cli_has_flags(&args, FLAG_RECURSIVE | FLAG_HIDDEN));
}

void test_cli_has_flags_returns_false_when_flag_is_not_set(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE,
	};

	TEST_ASSERT_FALSE(cli_has_flags(&args, FLAG_HIDDEN));
}

void test_cli_has_flags_returns_false_when_only_some_flags_are_set(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE,
	};

	TEST_ASSERT_FALSE(cli_has_flags(&args, FLAG_RECURSIVE | FLAG_HIDDEN));
}

void test_cli_add_flags_with_multiple_flags(void)
{
	struct cli_args args = {0};

	cli_add_flags(&args, FLAG_RECURSIVE | FLAG_HIDDEN | FLAG_VERBOSE);

	TEST_ASSERT_EQUAL_INT(FLAG_RECURSIVE | FLAG_HIDDEN | FLAG_VERBOSE,
			      args.flags);
}

void test_cli_remove_flags_with_multiple_flags(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE | FLAG_HIDDEN | FLAG_VERBOSE,
	};

	cli_remove_flags(&args, FLAG_RECURSIVE | FLAG_VERBOSE);

	TEST_ASSERT_EQUAL_INT(FLAG_HIDDEN, args.flags);
}

void test_cli_add_flags_does_not_clear_existing_flags(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE | FLAG_HIDDEN,
	};

	cli_add_flags(&args, FLAG_VERBOSE);

	TEST_ASSERT_EQUAL_INT(FLAG_RECURSIVE | FLAG_HIDDEN | FLAG_VERBOSE,
			      args.flags);
}

void test_cli_remove_flags_does_not_affect_unset_flags(void)
{
	struct cli_args args = {
	    .flags = FLAG_RECURSIVE,
	};

	cli_remove_flags(&args, FLAG_HIDDEN);

	TEST_ASSERT_EQUAL_INT(FLAG_RECURSIVE, args.flags);
}



int main(void)
{
	UNITY_BEGIN();


    RUN_TEST(test_cli_add_flags_sets_flag);
	RUN_TEST(test_cli_add_flags_preserves_existing_flags);
	RUN_TEST(test_cli_remove_flags_clears_flag);
	RUN_TEST(test_cli_remove_flags_preserves_other_flags);
	RUN_TEST(test_cli_has_flags_returns_true_when_all_flags_are_set);
	RUN_TEST(test_cli_has_flags_returns_false_when_flag_is_not_set);
	RUN_TEST(test_cli_has_flags_returns_false_when_only_some_flags_are_set);
	RUN_TEST(test_cli_add_flags_with_multiple_flags);
	RUN_TEST(test_cli_remove_flags_with_multiple_flags);
	RUN_TEST(test_cli_add_flags_does_not_clear_existing_flags);
	RUN_TEST(test_cli_remove_flags_does_not_affect_unset_flags);

	RUN_TEST(test_cli_add_flags_sets_flag);
	RUN_TEST(test_cli_add_flags_preserves_existing_flags);
	RUN_TEST(test_cli_remove_flags_clears_flag);
	RUN_TEST(test_cli_remove_flags_preserves_other_flags);
	RUN_TEST(test_cli_has_flags_returns_true_when_all_flags_are_set);
	RUN_TEST(test_cli_has_flags_returns_false_when_flag_is_not_set);
	RUN_TEST(test_cli_has_flags_returns_false_when_only_some_flags_are_set);
	RUN_TEST(test_cli_add_flags_with_multiple_flags);
	RUN_TEST(test_cli_remove_flags_with_multiple_flags);
	RUN_TEST(test_cli_add_flags_does_not_clear_existing_flags);
	RUN_TEST(test_cli_remove_flags_does_not_affect_unset_flags);

	return UNITY_END();
}
