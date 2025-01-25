#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "utils.h"

// implement parsing the headers and related data first
typedef struct
{
    List headers;
    int numCols;
    // add column and main data handling later
} DataFrame;

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

DataFrame parse_file_text(char *text)
{
    char *headersText = strtok(text, "\n");

    List headers = list_initialize();
    char *currentHeader = strtok(headersText, ",");
    DataFrame parsedText = {
        // initialize DataFrame that will store the file data
        .headers = headers,
        .numCols = 0,
    };

    do
    {
        list_append(&parsedText.headers, currentHeader);
        parsedText.numCols++;

        currentHeader = strtok(NULL, ",");
    } while (currentHeader);

    return parsedText;
}

void dataframe_print(DataFrame dataframe) {
    printf("HEADERS:\n");
    list_print(dataframe.headers);

    printf("\nNUMCOLS: %i", dataframe.numCols);
}

int main(void)
{
    FILE *ratingsFile = fopen("./data/ratings.csv", "r");
    if (!ratingsFile)
    {
        throw_error("issue opening file");
        return EXIT_FAILURE;
    }

    char *fileText = get_file_text(ratingsFile);

    DataFrame parsedFileText = parse_file_text(fileText);
    
    dataframe_print(parsedFileText);

    fclose(ratingsFile);
    free(fileText);

    return EXIT_SUCCESS;
}