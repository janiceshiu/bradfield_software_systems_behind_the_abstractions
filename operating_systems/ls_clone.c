#include <dirent.h> // contains directory-related functions and the `dirent` struct
#include <stdio.h>
#include <unistd.h> // contains the `optind` variable

int ls_files(const char *path) {
  DIR *directory_ptr = opendir(path);

  if (directory_ptr == NULL) {
    printf("Could not open directory %s\n", path);
    return 1;
  }

  while (1) {
    struct dirent *entry;

    entry = readdir(directory_ptr);
    if (entry == NULL) {
      break;
    }

    printf("%s\n", entry->d_name);
  }

  // We get a segmentation fault if we try to close a directory that doesn't exist.
  // This is because our program is trying to close a null pointer
  closedir(directory_ptr);

  return 0;
}

int main(int argc, char *argv[]) {
  // From the man page for `optind`:
  // The variable `optind` is the index of the next element to be
  //  processed in argv.  The system initializes this value to 1.  The
  //  caller can reset it to 1 to restart scanning of the same argv, or
  //  when scanning a new argument vector.
  return ls_files(argv[optind]);
}
