#ifndef CLI_H
#define CLI_H

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * struct cli_args - Command-line arguments used by seek.
 * @target: String to search for. The structure does not own this string.
 * @path: Starting path to search.
 * @flags: Search and command-line option flags.
 */
struct cli_args {
	const char *target;
	char path[PATH_MAX];
	int flags;
};


/**
 * @brief Initialize CLI arguments.
 *
 * @param args CLI arguments structure to initialize.
 * @param target Target string to search for.
 * @param path Starting path for the search.
 */
void cli_init(struct cli_args *args, const char *target, const char *path);

/**
 * @brief Add the specified flags to the CLI arguments.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to add.
 */
void cli_add_flags(struct cli_args *args, int flags);

/**
 * @brief Remove the specified flags from the CLI arguments.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to remove.
 */
void cli_remove_flags(struct cli_args *args, int flags);

/**
 * @brief Check whether all specified flags are set.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to check.
 *
 * @return true if all specified flags are set, otherwise false.
 */
bool cli_has_flags(const struct cli_args *args, int flags);

#endif // CLI_H
