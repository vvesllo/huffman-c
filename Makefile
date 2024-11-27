all:
	gcc -c coder.h coder.c
	gcc -c literal.h literal.c
	gcc -shared literal.o coder.o -o build/huffman.dll
	gcc main.c build/huffman.dll -o build/huffman.exe