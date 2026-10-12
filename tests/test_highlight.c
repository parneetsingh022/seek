#include "unity.h"

#include <seek/highlight.h>
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

/* Capture the function's output and compare every byte. */
static void assert_output(const char *text, size_t text_length,
			  const char *pattern, size_t pattern_length,
			  const char *expected, size_t expected_length)
{
	char actual[256];
	FILE *output = tmpfile();

	TEST_ASSERT_NOT_NULL(output);

	print_highlighted(output, text, text_length, pattern, pattern_length);

	rewind(output);
	size_t actual_length = fread(actual, 1, sizeof(actual), output);
	fclose(output);

	TEST_ASSERT_EQUAL_UINT(expected_length, actual_length);
	if (expected_length > 0)
		TEST_ASSERT_EQUAL_MEMORY(expected, actual, expected_length);
}

/* sizeof includes the final '\0', which we don't want to print. */
#define ASSERT_OUTPUT(text, pattern, expected)                              \
	assert_output(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1,     \
		      expected, sizeof(expected) - 1)

void test_highlights_match_at_beginning(void)
{
	ASSERT_OUTPUT("cat sleeps", "cat", "\x1b[32mcat\x1b[0m sleeps");
}

void test_highlights_match_in_middle(void)
{
	ASSERT_OUTPUT("the cat sleeps", "cat",
		      "the \x1b[32mcat\x1b[0m sleeps");
}

void test_highlights_match_at_end(void)
{
	ASSERT_OUTPUT("the cat", "cat", "the \x1b[32mcat\x1b[0m");
}

void test_highlights_multiple_matches(void)
{
	ASSERT_OUTPUT("cat and cat", "cat",
		      "\x1b[32mcat\x1b[0m and \x1b[32mcat\x1b[0m");
}

void test_highlights_adjacent_matches(void)
{
	ASSERT_OUTPUT("catcat", "cat",
		      "\x1b[32mcat\x1b[0m\x1b[32mcat\x1b[0m");
}

void test_uses_nonoverlapping_matches(void)
{
	ASSERT_OUTPUT("aaa", "aa", "\x1b[32maa\x1b[0ma");
}

void test_prints_text_unchanged_when_no_match_exists(void)
{
	ASSERT_OUTPUT("the dog sleeps", "cat", "the dog sleeps");
}

void test_prints_text_unchanged_when_pattern_is_longer(void)
{
	ASSERT_OUTPUT("cat", "caterpillar", "cat");
}

void test_prints_text_unchanged_for_empty_pattern(void)
{
	ASSERT_OUTPUT("the cat", "", "the cat");
}

void test_prints_nothing_for_empty_text(void)
{
	ASSERT_OUTPUT("", "cat", "");
}

void test_handles_null_bytes_in_text(void)
{
	ASSERT_OUTPUT("a\0cat", "cat", "a\0\x1b[32mcat\x1b[0m");
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_highlights_match_at_beginning);
	RUN_TEST(test_highlights_match_in_middle);
	RUN_TEST(test_highlights_match_at_end);
	RUN_TEST(test_highlights_multiple_matches);
	RUN_TEST(test_highlights_adjacent_matches);
	RUN_TEST(test_uses_nonoverlapping_matches);
	RUN_TEST(test_prints_text_unchanged_when_no_match_exists);
	RUN_TEST(test_prints_text_unchanged_when_pattern_is_longer);
	RUN_TEST(test_prints_text_unchanged_for_empty_pattern);
	RUN_TEST(test_prints_nothing_for_empty_text);
	RUN_TEST(test_handles_null_bytes_in_text);
	return UNITY_END();
}