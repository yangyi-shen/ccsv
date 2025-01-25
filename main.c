#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **pointer; // pointer to a pointer of a char (array of array of chars) (array of strings)
    size_t length;  // number of items in the List
} List;

List list_initialize(void)
{
    List newList = {
        .pointer = NULL, // list starts out empty
        .length = 0,     // number of items is 0
    };

    return newList;
}

void list_append(List *list, char *value)
{
    list->pointer = realloc(list->pointer, sizeof(char *) * (list->length + 1)); // reallocate enough space for current contents + 1 char
    list->pointer[list->length] = strdup(value);                                 // assign new value to newly created index
    list->length++;                                                              // update length to match current contents
}

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