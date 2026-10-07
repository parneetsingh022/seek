#include <seek/search.h>

const char* seek_find(const char* text, size_t text_length, const char* pattern,
		      size_t pattern_length)
{
	if (pattern_length == 0) {
		return text; // Empty pattern matches at the beginning of the
			     // text.
	}
	if (pattern_length > text_length) {
		return NULL; // A pattern longer than the text cannot possibly
			     // match.
	}

	size_t bad_match_shift_table[256];
	for (size_t character = 0; character < 256; character++) {
		bad_match_shift_table[character] = pattern_length;
	}

	size_t shift;
	for (size_t index = 0; index < pattern_length - 1; index++) {
		shift = pattern_length - 1 - index;
		bad_match_shift_table[(unsigned char)pattern[index]] = shift;
	}

	// Search for the pattern in the text using the bad match table
	size_t position = 0;
	while (position <= text_length - pattern_length) {
		size_t comparison_index = pattern_length;
		while (comparison_index > 0 &&
		       text[position + comparison_index - 1] ==
			   pattern[comparison_index - 1]) {
			comparison_index--;
		}
		if (comparison_index == 0) {
			return text + position; // A full match was found at
						// this offset.
		}
		position += bad_match_shift_table[(
		    unsigned char)text[position + pattern_length -
				       1]]; // Shift the position based on the
					    // bad match table
	}

	return NULL; // No match was found in the text.
}