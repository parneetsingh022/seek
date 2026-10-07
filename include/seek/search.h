#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

/*
 * seek_find() searches for the first occurrence of a pattern within a byte
 * sequence and returns a pointer into the original text buffer.
 *
 * The function uses a bad-character shift strategy to move the
 * search window efficiently through the text.
 *
 * Parameters:
 *  - text: the buffer to search within
 *  - text_length: number of bytes in text
 *  - pattern: the byte sequence to look for
 *  - pattern_length: number of bytes in pattern
 *
 * Return values:
 *  - If the pattern is empty, it returns text. This is the conventional
 *    behavior for string-search routines: an empty pattern matches at the
 *    beginning of the text.
 *  - If the pattern is longer than the text, it returns NULL because the
 *    pattern cannot fit in the remaining search space.
 *  - If a match is found, it returns a pointer to the first byte of the
 *    match inside text.
 *  - If no match is found, it returns NULL.
 *
 * Note: the returned pointer points into the original text buffer and must not
 * be freed by the caller.
 */
const char *seek_find( const char *text, size_t text_length, const char *pattern, size_t pattern_length);

#endif