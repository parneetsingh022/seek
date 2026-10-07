#include <seek/cli.h>

/**
 * @brief Add the specified flags to the CLI arguments.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to add.
 */
void cli_add_flags(struct cli_args *args, int flags)
{
	args->flags |= flags;
}

/**
 * @brief Remove the specified flags from the CLI arguments.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to remove.
 */
void cli_remove_flags(struct cli_args *args, int flags)
{
	args->flags &= ~(flags);
}

/**
 * @brief Check whether all specified flags are set.
 *
 * @param args CLI arguments structure.
 * @param flags Flags to check.
 *
 * @return true if all specified flags are set, otherwise false.
 */
bool cli_has_flags(const struct cli_args *args, int flags)
{
	return (args->flags & flags) == flags;
}
