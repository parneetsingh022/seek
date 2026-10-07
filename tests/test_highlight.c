#include "unity.h"
#include <seek/highlight.h>

void setUp(void) {}

void tearDown(void) {}

/*--------------------------------*/
/* Test cases for print_highlighted() */
/*--------------------------------*/

// Helper function to assert that the output of print_highlighted matches the
// expected output.
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
	TEST_ASSERT_EQUAL_MEMORY(expected, actual, expected_length);
}

/* Empty pattern should print the text without changes. */
void test_print_highlighted_with_empty_pattern(void)
{
	const char text[] = "hello world";
	const char pattern[] = "";
	const char expected[] = "hello world";

	assert_output(text, sizeof(text) - 1, pattern, 0, expected,
		      sizeof(expected) - 1);
}

/* A match should be printed with green ANSI highlighting. */
void test_print_highlighted_highlights_match(void)
{
	const char text[] = "hello world";
	const char pattern[] = "world";
	const char expected[] = "hello \x1b[32mworld\x1b[0m";

	assert_output(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1,
		      expected, sizeof(expected) - 1);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_print_highlighted_with_empty_pattern);
	RUN_TEST(test_print_highlighted_highlights_match);
	return UNITY_END();
}