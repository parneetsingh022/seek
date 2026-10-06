#ifndef __WALK_H
#define __WALK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

typedef void (*walk_callback)(const char *path, struct stat *info);

/**
 * walks through all entries in a directory and invokes the callback
 * for each entry that can be successfully inspected with stat().
 *
 * @param dir_name path to the directory to walk.
 * @param func     callback invoked for each directory entry.
 */
void walk_dir(const char *dir_name, walk_callback func);

#endif // __WALK_H
