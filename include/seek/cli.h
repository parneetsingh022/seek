#ifndef CLI_H
#define CLI_H

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * struct cli_args - Command-line arguments used by seek.
 * @target: String to search for. The structure does not own this string.
 * @path: Starting path to search.
 * @flags: Search and command-line option flags.
 */
struct cli_args {
	char *target;
	char path[PATH_MAX];
	int flags;
};

void cli_add_flags(struct cli_args *args, int flags);
void cli_remove_flags(struct cli_args *args, int flags);
bool cli_has_flags(const struct cli_args *args, int flags);

#endif // CLI_H
