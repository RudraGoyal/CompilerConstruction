#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

int print_options()
{
	printf("Select one of the following options (please type in an integer) :\n");
	printf("Press 0 : To exit the program\n");
	printf("Press 1 : For removal of comments\n");
	printf("Press 2 : For printing the token list generated by the lexer\n");
	printf("Press 3 : Verify the syntactic correctness of the input source code and printing the parse tree\n");
	printf("Press 4 : For printing the total time taken by the project code of lexer\n");
}

void print_intro()
{
	printf("FIRST and FOLLOW sets automated.\n");
	printf("Only Lexical analyzer module developed\n");
	printf("Both lexical and syntax analysis modules implemented\n");
	printf("Modules compile but give segmentation fault\n");
	printf("Modules work with testcases 2, 3 and 4 only\n");
	printf("Parse tree could not be constructed\n");
	printf("\n");
}

void print_token_list(FILE *fp, symTable *map, lex_header *lex_list)
{
	getStream(fp);
	print(fp, map, lex_list);
}

int main()
{
	symTable *map = initsymbolTable();
	lex_header *lex_list = create_Larray();
	int option;
	FILE *fp;
	fp = fopen("TestCases/t2.txt", "r");
	while (1)
	{
		print_options();
		scanf("%d", &option);
		switch (option)
		{
		case 0:
			printf("0\n");
			break;
		case 1:
			printf("1\n");
			removeComments(fp);
			break;
		case 2:
			printf("2\n");
			print_token_list(fp, map, lex_list);
			break;
		case 3:
			printf("3\n");
			break;
		case 4:
			printf("4\n");
			break;
		default:
			printf("Please choose a Valid Option\n");
		}
		rewind(fp);
		if (option == 0)
		{
			printf("-------Exiting-------\n");
			break;
		}
	}
}