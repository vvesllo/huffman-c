#include "coder.h"

void shannon_fano(Literal* literals, char* branch, char* fullBranch, int start, int end)
{
    char* code_branch = concat(fullBranch, branch);

    if (start == end)
    {
        literals[start].code = code_branch;
        return;
    }

    double average=0;
    int i;

    for (i = start; i <= end; i++) average += literals[i].freq;

    average /= 2.;

    i = start;
    int S = 0;

    while ((S + literals[i].freq < average) && (i < end))
    {
        S += literals[i].freq;
        i++;
    }

    shannon_fano(literals, "1", code_branch, start, i);
    shannon_fano(literals, "0", code_branch, i+1, end);
}


char* decode(char* input, Literal* literals, size_t size)
{
    char* decoded = "";
    for (int i = 0; i < strlen(input); i++)
        decoded = concat(decoded, literal_find_by_value(literals, size, input[i])->code);
    
    return decoded;
}

char* encode(char* decoded_str, Literal* literals, size_t size)
{
    char* encoded = "";
    char* code = "";
    
    for (int i = 0; i < strlen(decoded_str); i++)
    {
        code = concat(code, (char[2]){decoded_str[i], '\0'});
        Literal* lit = literal_find_by_code(literals, size, code);

        if (!(lit == NULL))
        {
            encoded = concat(encoded, &lit->value);
            code = "";
        }
    }
    return encoded;
}
