#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

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

char *get_file_contents(FILE *file)
{
    const long fileSize = get_file_size(file);
    char *fileContents = malloc(fileSize + 1); // add 1 to fileSize to reserve space for the null terminator
    if (!fileContents)
    {
        throw_error("issue allocating memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(fileContents, 1, fileSize, file); // read file in fileSize chunks of 1 byte
    fileContents[fileSize] = '\0';          // null-terminate

    return fileContents;
}

int main(void)
{
    FILE *ratingsFile = fopen("./data/ratings.csv", "r");
    if (!ratingsFile)
    {
        throw_error("issue opening file");
        return EXIT_FAILURE;
    }

    char *fileContents = get_file_contents(ratingsFile);

    char *ratingsFieldsRaw = strtok(fileContents, "\n");

    List ratingsFields = list_initialize();
    char *ratingsField = strtok(ratingsFieldsRaw, ",");
    do
    {
        list_append(&ratingsFields, ratingsField);
        printf("%s\n", ratingsField);
        ratingsField = strtok(NULL, ",");
    } while (ratingsField);

    fclose(ratingsFile);
    free(fileContents);

    return EXIT_SUCCESS;
}