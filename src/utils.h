#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

void throw_error(char *message);

FILE *csv_open(char *file_path);

long csv_getsize(FILE *file);

char *csv_gettext(FILE *file);

#endif