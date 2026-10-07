#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>

/**
 * @brief Searches for the first occurrence of a pattern within a byte sequence.
 *
 * This function scans the text using a bad-character shift table and returns a
 * pointer to the first match found inside the original text buffer.
 *
 * @param text Pointer to the buffer to search.
 * @param text_length Number of bytes in the text buffer.
 * @param pattern Pointer to the pattern to search for.
 * @param pattern_length Number of bytes in the pattern.
 *
 * @return Pointer to the first byte of the match, or `NULL` if no match
 *         exists. If `pattern_length` is zero, returns `text`.
 *
 * @note The returned pointer points into the original text buffer and must not
 * be freed by the caller.
 */
const char *seek_find(const char *text, size_t text_length, const char *pattern, size_t pattern_length);

#endif