#include <seek/highlight.h>
#include <seek/search.h>

#include <stdlib.h>

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

void seek_search(FILE *output, const char *path, const char *pattern,
		 size_t pattern_length)
{
	FILE *file = fopen(path, "rb");
	if (file == NULL)
		return;

	char *line = NULL;
	size_t capacity = 0;
	ssize_t length;
	size_t line_number = 0;
	int printed_path = 0;

	while ((length = getline(&line, &capacity, file)) != -1) {
		line_number++;

		size_t line_length = (size_t)length;
		if (line_length > 0 && line[line_length - 1] == '\n')
			line_length--;

		if (seek_find(line, line_length, pattern, pattern_length) ==
		    NULL)
			continue;

		if (!printed_path) {
			fprintf(output, "%s:\n", path);
			printed_path = 1;
		}

		fprintf(output, "%zu:", line_number);
		print_highlighted(output, line, line_length, pattern,
				  pattern_length);
		fputc('\n', output);
	}

	free(line);
	fclose(file);
}
