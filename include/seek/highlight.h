#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Prints text with every occurrence of pattern highlighted in red.
 *
 * An empty pattern prints the text without highlighting.
 * This function does not add a newline.
 *
 * @param output Stream to write the highlighted output to.
 * @param text Text buffer to print.
 * @param text_length Number of bytes in text.
 * @param pattern Pattern to highlight.
 * @param pattern_length Number of bytes in pattern.
 */
void print_highlighted(FILE *output, const char *text, size_t text_length,
		       const char *pattern, size_t pattern_length);

#endif