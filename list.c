#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

typedef struct
{
    void **contents; // pointer to a pointer (array of array of pointers)
    size_t length;   // number of items in the List
} List;

List list_initialize(void)
{
    List newList = {
        .contents = NULL, // list starts out empty
        .length = 0,      // number of items is 0
    };

    return newList;
}

void list_append(List *list, void *value)
{
    list->contents = realloc(list->contents, sizeof(void *) * (list->length + 1)); // reallocate enough space for current contents + 1 char
    if (!list->contents)
    {
        throw_error("issue allocating memory");
        exit(EXIT_FAILURE);
    }
    list->contents[list->length] = value; // assign new value to newly created index
    list->length++;                       // update length to match current contents
}

void list_print(List list)
{
    for (int i = list.length; i > 0; i--)
    {
        printf("ITEM %i: %s\n", i, list.contents[i - 1]);
    }
}