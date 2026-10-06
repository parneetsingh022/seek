#include <seek/walk.h>

/**
 * Determines whether a directory entry refers to the current directory
 * (".") or the parent directory ("..").
 *
 * @param entry Directory entry to check.
 * @return true if the entry is "." or "..", false otherwise.
 */
static bool is_special_dir(const struct dirent *entry);

void walk_dir(const char *dir_name, walk_callback func, bool recursive)
{
  DIR *dir;
  struct dirent *entry;

  if (!(dir = opendir(dir_name))){
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    // Skip '.' and '..' dirs
    if (is_special_dir(entry))
      continue;

    
    // Construct the full path: "dir_name/entry_name"
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);    

    struct stat info;

    if ((stat(path, &info)) != 0)
      continue;

    func(path, &info);
    // Recursively walk into subdirectories when enabled.
    if (recursive && S_ISDIR(info.st_mode))
      walk_dir(path, func, recursive);
  }

  closedir(dir);
}

static bool is_special_dir(const struct dirent *entry)
{
  return strcmp(entry->d_name, ".") == 0
         || strcmp(entry->d_name, "..") == 0;
}
