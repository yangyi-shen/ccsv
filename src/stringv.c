#include <string.h>

#include "utils.h"

typedef struct
{
    char **strings;
    size_t size;
    size_t size_allocated;
} stringv;

stringv *stringv_init(const int initial_size)
{
    // make sure parameters are valid
    if (initial_size <= 0)
    {
        throw_error("stringv_init() parameters invalid");
    }

    stringv *vector = malloc(sizeof(*vector));
    if (!vector)
    {
        throw_error("stringv_init() parameters invalid");
    }

    vector->strings = malloc(sizeof(char *) * initial_size);
    if (!vector->strings)
    {
        throw_error("malloc failed");
    }

    vector->size = 0;
    vector->size_allocated = initial_size;

    return vector;
}

void stringv_append(stringv *vector, const char *new_string)
{
    // make sure parameters are valid
    if (!vector || !new_string)
    {
        throw_error("stringv_append parameters invalid");
    }

    // check if reallocation necessary
    if (vector->size == vector->size_allocated)
    {
        // double allocated memory
        char **allocated_memory = realloc(vector->strings, sizeof(char *) * (vector->size_allocated * 2));
        if (!allocated_memory)
        {
        throw_error("realloc failed");
        }
        vector->strings = allocated_memory;

        // update size_allocated
        vector->size_allocated *= 2;
    }

    vector->strings[vector->size] = strdup(new_string); // duplicate new_string to use new pointer
    if (!vector->strings[vector->size])
    {
        throw_error("strdup failed");
    }

    // update other attributes
    vector->size++;
}

stringv *stringv_duplicate(const stringv vector) {
    stringv *duplicate = stringv_init(vector.size);

    for (int i = 0; i < vector.size; i++) {
        stringv_append(duplicate, vector.strings[i]);
    }

    return duplicate;
}

void stringv_free(stringv *vector)
{
    if (!vector)
    {
        throw_error("stringv_free() parameters invalid");
    }

    // free all char * in strings
    for (size_t i = 0; i < vector->size; i++)
    {
        free(vector->strings[i]);
    }
    free(vector->strings);
    free(vector);
}