#ifndef LITERAL_H
#define LITERAL_H

#include <stdlib.h>
#include <string.h>

typedef struct LITERAL_STRUCT
{
    char value;
    char* code;
    float freq;
} Literal;

extern char* concat(const char *s1, const char *s2);

extern int compare(const void* a, const void* b);

extern Literal* literal_find_by_value(Literal* literals, size_t size, char value);

extern Literal* literal_find_by_code(Literal* literals, size_t size, char* code);

#endif