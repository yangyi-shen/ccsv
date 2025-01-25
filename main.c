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