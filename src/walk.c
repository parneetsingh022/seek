#include <seek/walk.h>

static bool
is_special_dir(const struct dirent *entry);

void walk_dir(char *dir_name)
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
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);    

    struct stat info;

    if ((stat(path, &info)) == 0) { 
      if (S_ISDIR(info.st_mode)) {
        // if a directory
        printf("[DIR] %s\n", path);
        walk_dir(path);
      } else if(S_ISREG(info.st_mode)) {
        // If a regular file
        printf("[FILE] %s\n", path);
      }
    }
  }

  closedir(dir);
}



static bool
is_special_dir(const struct dirent *entry)
{
  return strcmp(entry->d_name, ".") == 0
         || strcmp(entry->d_name, "..") == 0;
}
