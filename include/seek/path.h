#ifndef __PATH_H
#define __PATH_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>

bool path_is_abs(const char *path);
bool get_abs_path(const char *path);
 
#endif
