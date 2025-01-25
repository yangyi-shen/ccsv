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

int main(void)
{
    FILE *ratingsFile = fopen("./data/ratings.csv", "r");

    if (!ratingsFile)
    {
        throw_error("issue opening file");
        return EXIT_FAILURE;
    }

    fseek(ratingsFile, 0L, SEEK_SET);

    const long fileSize = get_file_size(ratingsFile);
    unsigned char *fileContents = malloc(fileSize + 1); // add 1 to fileSize to reserve space for the null terminator
    if (!fileContents)
    {
        throw_error("issue allocating memory");
        fclose(ratingsFile);
        return EXIT_FAILURE;
    }

    fread(fileContents, 1, fileSize, ratingsFile); // read file in fileSize chunks of 1 byte
    fileContents[fileSize] = '\0';                 // null-terminate

    printf("%s", fileContents); // NOTE: full file will not print out due to terminal 1024 character limit
    fclose(ratingsFile);
    free(fileContents);

    return EXIT_SUCCESS;
}