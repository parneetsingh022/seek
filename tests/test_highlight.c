#include "unity.h"

#include <seek/highlight.h>
#include <stdio.h>

void setUp(void) {}

void tearDown(void) {}

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
#define ASSERT_OUTPUT(text, pattern, expected)                                 \
	assert_output(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1,    \
		      expected, sizeof(expected) - 1)

/* A match at the start of the text is wrapped in green ANSI codes. */
void test_highlights_match_at_beginning(void)
{
	ASSERT_OUTPUT("cat sleeps", "cat", "\x1b[32mcat\x1b[0m sleeps");
}

/* Text before and after a match remains unchanged. */
void test_highlights_match_in_middle(void)
{
	ASSERT_OUTPUT("the cat sleeps", "cat", "the \x1b[32mcat\x1b[0m sleeps");
}

/* A match ending at the end of the text is highlighted. */
void test_highlights_match_at_end(void)
{
	ASSERT_OUTPUT("the cat", "cat", "the \x1b[32mcat\x1b[0m");
}

/* Every separate occurrence of the pattern is highlighted. */
void test_highlights_multiple_matches(void)
{
	ASSERT_OUTPUT("cat and cat", "cat",
		      "\x1b[32mcat\x1b[0m and \x1b[32mcat\x1b[0m");
}

/* Adjacent matches receive separate highlight sequences. */
void test_highlights_adjacent_matches(void)
{
	ASSERT_OUTPUT("catcat", "cat", "\x1b[32mcat\x1b[0m\x1b[32mcat\x1b[0m");
}

/* Matches do not overlap; unmatched trailing bytes remain plain. */
void test_uses_nonoverlapping_matches(void)
{
	ASSERT_OUTPUT("aaa", "aa", "\x1b[32maa\x1b[0ma");
}

/* If the pattern is absent, the text is printed unchanged. */
void test_prints_text_unchanged_when_no_match_exists(void)
{
	ASSERT_OUTPUT("the dog sleeps", "cat", "the dog sleeps");
}

/* A pattern longer than the text cannot match. */
void test_prints_text_unchanged_when_pattern_is_longer(void)
{
	ASSERT_OUTPUT("cat", "caterpillar", "cat");
}

/* An empty pattern prints all text without highlighting. */
void test_prints_text_unchanged_for_empty_pattern(void)
{
	ASSERT_OUTPUT("the cat", "", "the cat");
}

/* Empty input produces no output. */
void test_prints_nothing_for_empty_text(void)
{
	ASSERT_OUTPUT("", "cat", "");
}

/* Matching uses explicit lengths and preserves embedded null bytes. */
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