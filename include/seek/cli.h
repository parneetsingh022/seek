#ifndef CLI_H
#define CLI_H

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// seek <pattern>

/**
 * struct cli_options - Command-line arguments used by seek.
 * @target: String to search for. The structure does not own this string.
 * @path: Starting path to search.
 * @flags: Search and command-line option flags.
 */
struct cli_options {
	const char *target;
	char path[PATH_MAX];
};

void cli_parse(struct cli_options *options, int argc, char *argv[]);

#endif // CLI_H