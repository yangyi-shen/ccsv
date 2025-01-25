#include <stdio.h>
#include <stdlib.h>

void throw_error(char *message)
{
    printf("\n\nERROR: %s\n", message);
}

long get_file_size(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    return fileSize;
}

char *get_file_text(FILE *file)
{
    const long fileSize = get_file_size(file);
    char *fileText = malloc(fileSize + 1); // add 1 to fileSize to reserve space for the null terminator
    if (!fileText)
    {
        throw_error("issue allocating memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(fileText, 1, fileSize, file); // read file in fileSize chunks of 1 byte
    fileText[fileSize] = '\0';          // null-terminate

    return fileText;
}