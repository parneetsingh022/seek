#include <stdio.h>
#include <seek/walk.h>

void print_paths(const char *path, struct stat *info) {
  if (S_ISDIR(info->st_mode)) {
    printf("[DIR!]: %s\n", path);
    walk_dir(path, print_paths);
  } else if(S_ISREG(info->st_mode)) {
    printf("[FILE!]: %s\n", path);
  }
}

int main() {
  walk_dir("/home/parneet/Workspace/seek", print_paths);

  return 0;
}
