#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    int fd;
    char *file_path = "example.txt"; 
    char buffer[100]; 
    int n;
    fd = open(file_path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

    write(fd, "This is an example file.\n", 24);
    lseek(fd, 0, SEEK_SET);
    n = read(fd, buffer, 100);
    buffer[n] = '\0';
    printf("File content: %s\n", buffer);
    close(fd);
    unlink(file_path);

    return 0;
}