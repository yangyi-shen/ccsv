#include <stdio.h>

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