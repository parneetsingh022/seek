#include "unity.h"
#include <seek/search.h>

void setUp(void) {}

void tearDown(void) {}

/*--------------------------------*/
/* Test cases for seek_find() */
/*--------------------------------*/

/* Pattern begins at position 0. */
void test_finds_pattern_at_beginning(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "too";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Pattern appears after the search algorithm shifts forward. */
void test_finds_pattern_at_end(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "brush";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 5, result);
}

/* Pattern appears in the middle of the text. */
void test_finds_pattern_in_middle(void)
{
	const char text[] = "xxneedlexx";
	const char pattern[] = "needle";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 2, result);
}

/* Pattern and text are exactly equal. */
void test_finds_pattern_equal_to_entire_text(void)
{
	const char text[] = "seek";
	const char pattern[] = "seek";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Missing pattern should return NULL. */
void test_returns_null_when_pattern_is_missing(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "comb";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_NULL(result);
}

/* A pattern longer than the text cannot match. */
void test_returns_null_when_pattern_is_longer_than_text(void)
{
	const char text[] = "cat";
	const char pattern[] = "caterpillar";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_NULL(result);
}

/* An empty pattern matches at the beginning. */
void test_empty_pattern_matches_at_beginning(void)
{
	const char text[] = "toothbrush";
	const char pattern[] = "";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* A one-character pattern should work. */
void test_finds_single_character_pattern(void)
{
	const char text[] = "abcdef";
	const char pattern[] = "d";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text + 3, result);
}

/* The first occurrence should be returned when matches overlap. */
void test_returns_first_overlapping_match(void)
{
	const char text[] = "aaaaa";
	const char pattern[] = "aaa";

	const char* result =
	    seek_find(text, sizeof(text) - 1, pattern, sizeof(pattern) - 1);

	TEST_ASSERT_EQUAL_PTR(text, result);
}

/* Search is currently case-sensitive. */
void test_search_is_case_sensitive(void)
{
	const char text[] = "seek";
	const char pattern[] = "Seek";

	const char* result =
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

	const char* result =
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

	const char* result =
	    seek_find(text, sizeof(text), pattern, sizeof(pattern));

	TEST_ASSERT_EQUAL_PTR(text + 1, result);
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

	return UNITY_END();
}