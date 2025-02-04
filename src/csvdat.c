#include "utils.h"
#include "stringv.h"

typedef struct
{
    stringv headers;
    stringv *rows;
    int num_cols;
    int num_rows;
} csvdat;

csvdat *csvdat_init(void)
{
    csvdat *data = malloc(sizeof(*data));
    if (!data)
    {
        throw_error("malloc failed");
    }

    stringv *data_headers = stringv_init(1);
    stringv *data_rows = malloc(sizeof(stringv));
    if (!data_rows)
    {
        throw_error("malloc failed");
    }

    data->headers = *data_headers;
    data->rows = data_rows;
    data->num_cols = 0;
    data->num_rows = 0;

    return data;
}

void csvdat_appendheader(csvdat *data, const char *new_header)
{
    char *new_header_duplicate = strdup(new_header);
    if (!new_header_duplicate)
    {
        throw_error("string duplication failed");
    }

    stringv_append(&data->headers, new_header_duplicate);

    data->num_cols++;
}

void csvdat_appendrow(csvdat *data, const stringv new_row)
{
    stringv *new_row_duplicate = stringv_duplicate(new_row);
    if (!new_row_duplicate)
    {
        throw_error("stringv_duplicate() failed");
    }

    stringv *allocated_memory = realloc(data->rows, sizeof(stringv) * (data->num_rows + 1));
    if (!allocated_memory)
    {
        free(new_row_duplicate); // de-allocate new_row_duplicate memory as it is never appended to data->rows
        throw_error("realloc failed");
    }
    else
    {
        data->rows = allocated_memory;
    }

    data->rows[data->num_rows] = *new_row_duplicate;
    data->num_rows++;
}

void csvdat_free(csvdat *data)
{
    stringv_free(&data->headers);

    // loop over and free each stored row
    for (int i = 0; i < data->num_rows; i++)
    {
        stringv_free(&data->rows[i]);
    }
    free(data->rows); // then, free rows itself which is a pointer

    free(data);
}