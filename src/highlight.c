#include <seek/highlight.h>

void print_highlighted(FILE *output, const char *text, size_t text_length,
		       const char *pattern, size_t pattern_length)
{
	const char *current = text;
	size_t remaining = text_length;

	if (pattern_length == 0) {
		fwrite(text, 1, text_length, output);
		return;
	}
	// Runs while there is enough text left to match the pattern and when
	// match returns NULL, we break
	while (remaining >= pattern_length) {
		const char *match =
		    seek_find(current, remaining, pattern, pattern_length);

		if (match == NULL)
			break;

		// write text before match normally
		size_t before_match = (size_t)(match - current);
		fwrite(current, 1, before_match, output);
		// Terminal switches to green color for matched pattern
		fputs("\x1b[32m", output);
		fwrite(match, 1, pattern_length, output);
		// Terminal switches back to default color
		fputs("\x1b[0m", output);

		// update current pointer and remaining length
		current = match + pattern_length;
		remaining -= before_match + pattern_length;
	}
	fwrite(current, 1, remaining, output);
}