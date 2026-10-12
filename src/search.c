#include <seek/highlight.h>
#include <seek/search.h>

const char *seek_find(const char *text, size_t text_length, const char *pattern,
		      size_t pattern_length)
{
	// Empty pattern matches at the beginning of the text.
	if (pattern_length == 0)
		return text;

	// A pattern longer than the text cannot possibly match.
	if (pattern_length > text_length)
		return NULL;

	size_t bad_match_shift_table[256];
	for (size_t character = 0; character < 256; character++)
		bad_match_shift_table[character] = pattern_length;

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

		// A full match was found at his offset.
		if (comparison_index == 0)
			return text + position;

		// Shift the position based on the bad match table
		position += bad_match_shift_table[(
		    unsigned char)text[position + pattern_length - 1]];
	}

	return NULL;
}

void seek_search(FILE *output, const char *text, size_t text_length,
		 const char *pattern, size_t pattern_length)
{
	size_t line_number = 1;
	size_t line_start = 0;

	while (line_start < text_length) {
		size_t line_end = line_start;
		while (line_end < text_length && text[line_end] != '\n')
			line_end++;

		size_t line_length = line_end - line_start;
		const char *line = text + line_start;
		if (seek_find(line, line_length, pattern, pattern_length) !=
		    NULL) {
			fprintf(output, "%zu:", line_number);
			print_highlighted(output, line, line_length, pattern,
					  pattern_length);
			fputc('\n', output);
		}

		line_start = line_end + (line_end < text_length ? 1 : 0);
		line_number++;
	}
}
