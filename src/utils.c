#include <stdio.h>
#include <stdlib.h>

void throw_error(char *message)
{
    fprintf(stderr, "\nERROR: %s\n\n", message);
}

FILE *csv_open(char *file_path)
{
    FILE *ratings_file = fopen(file_path, "r");
    if (!ratings_file)
    {
        throw_error("file open failed");
    }

    return ratings_file;
}

long csv_getsize(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    return file_size;
}

char *csv_gettext(FILE *file)
{
    const long file_size = csv_getsize(file);
    char *fileText = malloc(file_size + 1); // add 1 to file_size to reserve space for the null terminator
    if (!fileText)
    {
        fclose(file);
        throw_error("malloc failed");
    }

    fread(fileText, 1, file_size, file); // read file in file_size chunks of 1 byte
    fileText[file_size] = '\0';          // null-terminate

    return fileText;
}