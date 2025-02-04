#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "stringv.h"
#include "csvdat.h"

csvdat *csv_parse(const char *text)
{
    // make copy of csv text so original isn't modifided
    char *text_copy = strdup(text);
    if (!text_copy)
    {
        throw_error("string duplication failed");
    }

    csvdat *csv_data = csvdat_init();

    // extract headers, put into single stringv, then assign stringv to csv_data->headers
    char *headers_text = strtok(text_copy, "\n");
    char *current_header = strtok(headers_text, ",");
    do
    {
        csvdat_appendheader(csv_data, current_header);
        current_header = strtok(NULL, ",");
    } while (current_header);

    // loop over each row
    char *row_text = strtok(NULL, "\n");
    do
    {
        stringv *row = stringv_init(1);              // create new stringv to hold row data
        char *current_field = strtok(row_text, ","); // loop over each field in the row
        do
        {
            stringv_append(row, current_field); // add field data to row stringv
            current_field = strtok(NULL, ",");
        } while (current_field);

        csvdat_appendrow(csv_data, *row); // add filled row to csvdat variable
        row_text = strtok(NULL, "\n");
    } while (row_text);

    return csv_data;
}

int main(void)
{
    FILE *file = csv_open("data/ratings.csv");
    char *file_text = csv_gettext(file);

    csvdat *file_data = csv_parse(file_text);

    printf("%s", file_data->headers.strings[0]);

    csvdat_free(file_data);

    fclose(file);
    free(file_text);

    return EXIT_SUCCESS;
}