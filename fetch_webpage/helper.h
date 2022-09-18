#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#define WORD_MAX 50
#define BUFFER_MAX 200

typedef struct STRING {
    char *container;
    int length;
} String;

void print_array (int, char*);
//void print_char_array (int, char*);
void print_string (String);
void print_string_pointer (char*);

char* array_to_pointer (int, char*);
String concatenate_strings_faulty (int, ...);
void concatenate_strings (int*, char*, int, ...);

#endif