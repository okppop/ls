#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
// #include <sys/types.h>

const char *help = "usage: ls [-a] [path]\n";
int show_all;

int main(int argc, char *argv[]) {
  // flag parse
  int opt;
  while ((opt = getopt(argc, argv, "a")) != -1) {
    switch (opt) {
    case 'a':
      show_all = 1;
      break;
    default:
      fprintf(stderr, "%s", help);
      return 1;
    }
  }

  // open dir
  const char *path = (optind < argc) ? argv[optind] : ".";
  DIR *dir = opendir(path);
  if (!dir) {
    perror("open");
    return 1;
  }

  // loop entry
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (!show_all && entry->d_name[0] == '.')
      continue;
    printf("%s\n", entry->d_name);
  }

  // close dir
  int ret = closedir(dir);
  if (ret < 0) {
    perror("close");
    return ret;
  }
  return 0;
}
