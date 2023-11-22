#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    DIR *dir = opendir(argv[1]);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);

    return 0;
}