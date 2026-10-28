#include <seek/cli.h>
#include <seek/walk.h>

#include <stdio.h>

void print_paths(const char *path, struct stat *info)
{
    if (S_ISDIR(info->st_mode))
        printf("[DIR!]: %s\n", path);
    else if (S_ISREG(info->st_mode))
        printf("[FILE!]: %s\n", path);
}

int main(int argc, char *argv[])
{
    struct cli_options options = {0};

    cli_parse(&options, argc, argv);

    walk_dir(options.path, print_paths, true);

    return 0;
}