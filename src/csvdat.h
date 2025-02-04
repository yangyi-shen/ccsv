#ifndef CSVDAT_H
#define CSVDAT_H

#include "utils.h"
#include "stringv.h"

typedef struct
{
    stringv headers;
    stringv *rows;
    int num_cols;
    int num_rows;
} csvdat;

csvdat *csvdat_init(void);

void csvdat_appendheader(csvdat *data, const char *new_header);

void csvdat_appendrow(csvdat *data, const stringv new_row);

void csvdat_free(csvdat *data);

#endif