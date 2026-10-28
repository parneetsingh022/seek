#include <seek/cli.h>
#include <seek/search.h>
#include <seek/walk.h>

#include <stdio.h>
#include <string.h>

void print_matching_lines(const char *path, struct stat *info, void *userdata)
{
	const char *target = userdata;

	const struct search_options options = {
	    .search_binary = false,
	};

	if (S_ISREG(info->st_mode))
		seek_search(stdout, path, target, strlen(target), &options);
}

int main(int argc, char *argv[])
{
	struct cli_options options = {0};

	cli_parse(&options, argc, argv);

	walk_dir(options.path, print_matching_lines, (void *)options.target,
		 true);

	return 0;
}