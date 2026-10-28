#include <seek/cli.h>

void cli_parse(struct cli_options *options, int argc, char *argv[]) {
	if (argc != 2) {
		goto usage_error;
	}

	options->target = argv[1];
	strcpy(options->path, ".");

	return;

usage_error:
	fprintf(stderr, "usage: %s target\n", argv[0]);
	exit(EXIT_FAILURE);
}