#include <seek/search.h>

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

const char *seek_find( const char *text, size_t text_length, const char *pattern, size_t pattern_length){
    if (pattern_length == 0){
        return text; // Empty pattern matches at the beginning of the text.
    }
    if (pattern_length > text_length){
        return NULL; // A pattern longer than the text cannot possibly match.
    }

    size_t bad_match_shift_table[256];
    for (size_t character = 0; character < 256; character++){
        bad_match_shift_table[character] = pattern_length;
    }

    size_t shift;
    for (size_t index = 0; index < pattern_length - 1; index ++){
        shift = pattern_length - 1 - index;
        bad_match_shift_table[(unsigned char)pattern[index]] = shift;
    }

    // Search for the pattern in the text using the bad match table
    size_t position = 0;
    while (position <= text_length - pattern_length) {
        size_t comparison_index = pattern_length;
        while (comparison_index > 0 && text[position + comparison_index - 1] == pattern[comparison_index - 1]) {
            comparison_index--;
        }
        if (comparison_index == 0) {
            return text + position; // A full match was found at this offset.
        }
        position += bad_match_shift_table[(unsigned char)text[position + pattern_length - 1]]; // Shift the position based on the bad match table
    }

    return NULL; // No match was found in the text.
}