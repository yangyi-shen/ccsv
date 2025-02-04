#ifndef STRINGV_H
#define STRINGV_H

#include <string.h>

#include "utils.h"

typedef struct
{
    char **strings;
    size_t size;
    size_t size_allocated;
} stringv;

stringv *stringv_init(int initial_size);

void stringv_append(stringv *vector, const char *new_string);

stringv *stringv_duplicate(const stringv vector);

void stringv_free(stringv *vector);

#endif