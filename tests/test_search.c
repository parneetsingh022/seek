#include "unity.h"
#include <seek/search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void setUp(void) {}

void tearDown(void) {}

static void assert_search_output(const char *file_contents,
				 size_t file_contents_length,
				 const char *pattern, size_t pattern_length,
				 const char *expected_lines,
				 size_t expected_lines_length)
{
	char path[] = "/tmp/seek_test_search_XXXXXX";
	int file_descriptor = mkstemp(path);
	TEST_ASSERT_TRUE(file_descriptor >= 0);

	FILE *input = fdopen(file_descriptor, "wb");
	TEST_ASSERT_NOT_NULL(input);
	size_t written = fwrite(file_contents, 1, file_contents_length, input);
	int input_close_result = fclose(input);
	TEST_ASSERT_EQUAL_UINT(file_contents_length, written);
	TEST_ASSERT_EQUAL_INT(0, input_close_result);

	char actual[512];
	FILE *output = tmpfile();

	TEST_ASSERT_NOT_NULL(output);
	seek_search(output, path, pattern, pattern_length);
	rewind(output);
	size_t actual_length = fread(actual, 1, sizeof(actual), output);
	fclose(output);
	unlink(path);

	char expected[512];
	size_t expected_length = 0;
	if (expected_lines_length > 0) {
		int prefix_length =
		    snprintf(expected, sizeof(expected), "%s:\n", path);
		TEST_ASSERT_TRUE(prefix_length >= 0);
		expected_length = (size_t)prefix_length + expected_lines_length;
		TEST_ASSERT_TRUE(expected_length <= sizeof(expected));
		memcpy(expected + prefix_length, expected_lines,
		       expected_lines_length);
	}

	TEST_ASSERT_EQUAL_UINT(expected_length, actual_length);
	if (expected_length > 0)
		TEST_ASSERT_EQUAL_MEMORY(expected, actual, expected_length);
}

#define ASSERT_SEARCH_OUTPUT(file_contents, pattern, expected_lines)           \
	assert_search_output(file_contents, sizeof(file_contents) - 1,         \
			     pattern, sizeof(pattern) - 1, expected_lines,     \
			     sizeof(expected_lines) - 1)

/*--------------------------------*/
/* Test cases for seek_find() */
/*--------------------------------*/

/* Pattern begins at position 0. */
void test_finds_pattern_at_beginning(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "too";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Pattern appears after the search algorithm shifts forward. */
void test_finds_pattern_at_end(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "brush";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 5, result);
}

/* Pattern appears in the middle of the text. */
void test_finds_pattern_in_middle(void)
{
	const char text[] = "xxneedlexx";
	const char pattern[] = "needle";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 2, result);
}

/* Pattern and text are exactly equal. */
void test_finds_pattern_equal_to_entire_text(void)
{
	const char text[] = "seek";
	const char pattern[] = "seek";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Missing pattern should return NULL. */
void test_returns_null_when_pattern_is_missing(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "comb";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_NULL(result);
}

/* A pattern longer than the text cannot match. */
void test_returns_null_when_pattern_is_longer_than_text(void)
{
	const char text[] = "cat";
	const char pattern[] = "caterpillar";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_NULL(result);
}

/* An empty pattern matches at the beginning. */
void test_empty_pattern_matches_at_beginning(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* A one-character pattern should work. */
void test_finds_single_character_pattern(void)
{
	const char text[] = "abcdef";
	const char pattern[] = "d";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 3, result);
}

/* The first occurrence should be returned when matches overlap. */
void test_returns_first_overlapping_match(void)
{
	const char text[] = "aaaaa";
	const char pattern[] = "aaa";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Search is currently case-sensitive. */
void test_search_is_case_sensitive(void)
{
	const char text[] = "seek";
	const char pattern[] = "Seek";

	const char *result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_NULL(result);
}

/*
 * Length-based searching should support embedded null bytes.
 * This confirms that seek_find() does not depend on strlen().
 */
void test_finds_pattern_containing_null_byte(void)
{
	const char text[] = {'a', 'b', '\0', 'c', 'd'};
	const char pattern[] = {'\0', 'c'};

	const char *result =
	    seek_find(text, sizeof(text), pattern, sizeof(pattern));

	TEST_ASSERT_EQUAL_PTR(text + 2, result);
}

/*
 * Casting table indexes to unsigned char should allow all
 * possible byte values to be searched safely.
 */
void test_finds_non_ascii_byte(void)
{
	const char text[] = {'a', (char)0xFF, 'b'};
	const char pattern[] = {(char)0xFF, 'b'};

	const char *result =
	    seek_find(text, sizeof(text), pattern, sizeof(pattern));

	TEST_ASSERT_EQUAL_PTR(text + 1, result);
}

/* Matching lines are numbered by their original position and highlighted. */
void test_search_prints_numbered_matching_lines(void)
{
	ASSERT_SEARCH_OUTPUT(
	    "one cat\ncat two\nnone\nlast cat", "cat",
	    "1:one \x1b[32mcat\x1b[0m\n2:\x1b[32mcat\x1b[0m two\n"
	    "4:last \x1b[32mcat\x1b[0m\n");
}

/* A matching line is emitted only once even when it contains many matches. */
void test_search_prints_matching_line_once(void)
{
	ASSERT_SEARCH_OUTPUT("cat and cat\n", "cat",
			     "1:\x1b[32mcat\x1b[0m and "
			     "\x1b[32mcat\x1b[0m\n");
}

/* A matching final line gets a newline even if the input has none. */
void test_search_handles_final_line_without_newline(void)
{
	ASSERT_SEARCH_OUTPUT("first\nfind me", "find",
			     "2:\x1b[32mfind\x1b[0m me\n");
}

/* No output is produced when none of the lines contain the pattern. */
void test_search_prints_nothing_when_no_line_matches(void)
{
	ASSERT_SEARCH_OUTPUT("first\nsecond\n", "missing", "");
}

int main(void)
{
	UNITY_BEGIN();

	RUN_TEST(test_finds_pattern_at_beginning);
	RUN_TEST(test_finds_pattern_at_end);
	RUN_TEST(test_finds_pattern_in_middle);
	RUN_TEST(test_finds_pattern_equal_to_entire_text);
	RUN_TEST(test_returns_null_when_pattern_is_missing);
	RUN_TEST(test_returns_null_when_pattern_is_longer_than_text);
	RUN_TEST(test_empty_pattern_matches_at_beginning);
	RUN_TEST(test_finds_single_character_pattern);
	RUN_TEST(test_returns_first_overlapping_match);
	RUN_TEST(test_search_is_case_sensitive);
	RUN_TEST(test_finds_pattern_containing_null_byte);
	RUN_TEST(test_finds_non_ascii_byte);
	RUN_TEST(test_search_prints_numbered_matching_lines);
	RUN_TEST(test_search_prints_matching_line_once);
	RUN_TEST(test_search_handles_final_line_without_newline);
	RUN_TEST(test_search_prints_nothing_when_no_line_matches);

	return UNITY_END();
}