#ifndef CODER_H
#define CODER_H

#include <stdlib.h>
#include "literal.h"

extern void shannon_fano(Literal* literals, char* branch, char* fullBranch, int start, int end);

extern char* decode(char* input, Literal* literals, size_t size);

extern char* encode(char* decoded_str, Literal* literals, size_t size);


#endif