#include <stdio.h>
#include <math.h>
#include "literal.h"
#include "coder.h"

#pragma comment(lib, "huffman.dll")

char* read_file(const char* path);

void write_file(const char* path, char* data);


int main()
{
    char path[1024];
    char* input;

    printf("filepath > ");
    scanf("%s", path);

    if ((input = read_file(path)) == NULL)
    {
        printf("Failed to open file `%s`!\n", path);
        system("pause");
        return -1;
    }

    size_t size=0;
    size_t input_length=strlen(input);
    Literal* literals = (Literal*)calloc(size, sizeof(Literal));

    char current_char;
    
    for (size_t i=0; i<input_length; ++i)
    {
        current_char = input[i];
        Literal* lit;
        lit = literal_find_by_value(literals, size, current_char);
        
        if (lit == NULL)
        {
            literals = (Literal*)realloc(literals, ++size*sizeof(Literal));

            literals[size-1].freq = 1;
            literals[size-1].value = current_char;
        }
        else lit->freq++;

    }

    qsort(literals, size, sizeof(Literal), compare);

    shannon_fano(literals, "", "", 0, size);

    for (int i = 0; i < size; i++)
    {
        Literal lit = literals[i];
        printf("Literal: `%c` (frequiency=%f) -> code: %s\n", lit.value, lit.freq/input_length, lit.code);
    }

    char* decoded = decode(input, literals, size);
    printf("decoded: %s\n", decoded);
    write_file("output.bin", decoded);

    // -----------

    char* encoded = encode(decoded, literals, size);
    printf("encoded: %s\n", encoded);

    system("pause");
}

char* read_file(const char* path)
{
	FILE* file;
	char* buffer;
	long size, i=0;
    char ch;
  
	if ((file = fopen(path, "r")) == NULL)
		return NULL;

    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fseek(file, 0L, SEEK_SET);


	buffer = (char*)malloc((size+1) * sizeof(char));

	while((ch = fgetc(file)) != EOF)
		buffer[i++] = (char)ch;

	buffer[i] = '\0';

	fclose(file);
	return buffer;
}

void write_file(const char* path, char* data)
{
	FILE* file;
    
    file = fopen(path, "w");
    
    fprintf(file, data);

    fclose(file);
}

