#ifndef WALK_H
#define WALK_H

#include <dirent.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef void (*walk_callback)(const char* path, struct stat* info);

/**
 * Walks through all entries in a directory and invokes the callback
 * for each entry that can be successfully inspected with stat().
 *
 * If recursive is true, subdirectories are walked recursively.
 *
 * @param dir_name  path to the directory to walk.
 * @param func      callback invoked for each directory entry.
 * @param recursive whether to recursively walk subdirectories.
 */
void walk_dir(const char* dir_name, walk_callback func, bool recursive);

#endif // WALK_H
