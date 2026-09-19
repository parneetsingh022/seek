#include <seek/path.h>

/**
 * Checks whether a path is absolute.
 *
 * Note: This only works on POSIX system and relies on
 * leading '/' to determine if it is an absolute or relative path.
 *
 * @param path Path string to check.
 * @return true if the path is absolute, false otherwise.
 */
bool path_is_abs(const char *path)
{
  if (path == NULL || strlen(path) < 1)
    return false;

  return path[0] == '/';

}



