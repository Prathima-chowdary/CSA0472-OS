#include <stdio.h>
#include <stdlib.h>

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("File '%s' created successfully.\n", filename);
}

void writeFile(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");  
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", data);
    fclose(file);
    printf("Data written to file '%s' successfully.\n", filename);
}

void readFile(const char *filename) {
    FILE *file = fopen(filename, "r");  
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

int main() {
    const char *filename = "example_file.txt";
    const char *data = "Hello, this is a sample text.\n";
    createFile(filename);
    writeFile(filename, data);
    printf("\nData read from file:\n");
    readFile(filename);

    return 0;
}