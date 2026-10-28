#ifndef SEARCH_H
#define SEARCH_H

#include <stddef.h>
#include <stdio.h>

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
const char *seek_find(const char *text, size_t text_length, const char *pattern,
		      size_t pattern_length);

/**
 * @brief Prints lines containing a pattern from a file.
 *
 * If matches are found, the file path is printed on its own line, followed by
 * each matching line prefixed with its 1-based line number. Pattern matches
 * are highlighted. A final line without a newline is supported, and matching
 * output lines always end with a newline. If the file cannot be opened, no
 * output is written.
 *
 * @param output Stream to write matching lines to.
 * @param path Path to the file to search.
 * @param pattern Pattern to search for.
 * @param pattern_length Number of bytes in the pattern.
 */
void seek_search(FILE *output, const char *path, const char *pattern,
		 size_t pattern_length);

#endif // SEARCH_H
