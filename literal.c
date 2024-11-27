#include "literal.h"



char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int compare(const void* a, const void* b)
{
    Literal* literal_a = (Literal*)a;
    Literal* literal_b = (Literal*)b;
    return (literal_b->freq - literal_a->freq);
}

Literal* literal_find_by_value(Literal* literals, size_t size, char value)
{
    for (size_t i=0; i < size; i++)
        if (literals[i].value == value) return &literals[i];

    return NULL;
}

Literal* literal_find_by_code(Literal* literals, size_t size, char* code)
{
    for (size_t i=0; i < size; i++)
        if (strcmp(literals[i].code, code) == 0) return &literals[i];

    return NULL;
}