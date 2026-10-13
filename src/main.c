#include <seek/search.h>
#include <seek/walk.h>
#include <stdio.h>

void print_maching_lines(const char *path, struct stat *info)
{
	if (S_ISREG(info->st_mode))
		seek_search(stdout, path, "return", sizeof("return") - 1);
}

int main()
{
	walk_dir("src/", print_maching_lines, true);

	return 0;
}
