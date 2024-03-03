#include <stdio.h>
#include <stdlib.h>

#ifndef LEXERH
#define LEXERH

// Important Functions
int getStream(FILE *fp);
char read(int* end, FILE* fp);

// Error and Lexeme Handlers
char* ret_lexeme_error(int beg, int end);
char* ret_lexeme(int beg, int end);

// Utilities
void concatenate_string(char* s,int j, char* s1);
int isAlpha(char c);
void print(FILE* fp);


#endif