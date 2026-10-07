#include <seek/cli.h>


void cli_init(struct cli_args *args, const char *target, const char *path)
{
    args->target = target;
	snprintf(args->path, sizeof(args->path), "%s", path);
	args->flags = 0;
}

void cli_add_flags(struct cli_args *args, int flags)
{
	args->flags |= flags;
}


void cli_remove_flags(struct cli_args *args, int flags)
{
	args->flags &= ~(flags);
}


bool cli_has_flags(const struct cli_args *args, int flags)
{
	return (args->flags & flags) == flags;
}
