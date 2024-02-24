#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_SIZE 50
#define BUFFER_SIZE 5

typedef enum {
    TK_ASSIGNOP,
    TK_COMMENT,
    TK_SQR,
    TK_SQL,
    TK_UNKNOWN,
    TK_END,
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_TOKEN_SIZE];
} Token;const

// bool isspace(char c){
//     return c==' ';
// }

TokenType getTokenType(const char* lexeme){
    if(!strcmp(lexeme,"<--"))
    return TK_ASSIGNOP;
    else if(!strcmp(lexeme,"%%"))
    return TK_COMMENT;
    else if(!strcmp(lexeme,"["))
    return TK_SQL;
    else if(!strcmp(lexeme,"]"))
    return TK_SQR;
    else
    return TK_UNKNOWN;
}

Token getNextToken(FILE* fp, char buffer[][BUFFER_SIZE], int bufsize, int* bufferIndex) {
    Token token;
    token.type = TK_END;
    char lexeme[MAX_TOKEN_SIZE] = "";
    int lexemeIndex = 0;
    char c;

    while (1) {
        c = buffer[*bufferIndex][0];
        if (isspace(c) || c == '\0') {
            if (lexemeIndex > 0) {
                strncpy(token.lexeme, lexeme, lexemeIndex);
                token.lexeme[lexemeIndex] = '\0';
                token.type = getTokenType(token.lexeme);
                return token;
            }
            if (c == '\0') {
                break;
            }
            (*bufferIndex)++;
            continue;
        }
        lexeme[lexemeIndex++] = c;
        (*bufferIndex)++;
    }

    return token;
}

FILE* getStream(FILE* fp, char buffer[][BUFFER_SIZE], int bufsize) {
    int count;
    if (!feof(fp))
        count = fread(buffer[0], 1, bufsize, fp);

    if (count < bufsize)
        buffer[0][count] = '\0';

    return fp;
}

// FILE *getStream(FILE* fp,char* buffer,int bsize)
// {
// 	int count;
// 	if(!feof(fp))
// 		count=fread(buffer,1,bsize,fp);

// 	if(count<bsize)
// 	buffer[count] = '\0';

// 	return fp;

// }

// void removeComments(FILE *fp){
//     char c = fgetc(fp);
//     while (c!=EOF)
//     {
//         if(c=='%'){
//             while(c!='\n' && c!=EOF){
//                 c=fgetc(fp);
//             }
//         }
//         if(c==EOF)
//         break;
//         printf("%c",c);
//         c=fgetc(fp);
//     }
//     printf("\n");
    
// }

// int main()
// {
//     FILE *fp = fopen("t2.txt","r");
//     int bufsize=5;
//     char *buffer = (char*)malloc(bufsize);
//     if(fp==NULL){
//         printf("error opening file");
//     }
//     // while(!feof(fp)){
// 	// 	memset(buffer, 0, sizeof(buffer));
//     //     fp = getStream(fp,buffer,bufsize);
//     //     printf("%s\n",buffer);
//     // }
//     removeComments(fp);
//     fclose(fp);
//     // printf("hello\n");

//     return 0;
// }



int main() {
    FILE* fp = fopen("./TestCases/test.txt", "r");
    if (!fp) {
        perror("Error opening file");
        return -1;
    }

    char buffer[2][BUFFER_SIZE];

    // uncomment to remove comments
    // fp = getStream(fp, buffer, BUFFER_SIZE);
    // removeComments(fp, buffer, BUFFER_SIZE);

    // rewind(fp);
    fp = getStream(fp, buffer, BUFFER_SIZE);

    Token token;
    int bufferIndex = 0;
    do {
        token = getNextToken(fp, buffer, BUFFER_SIZE, &bufferIndex);
        switch (token.type) {
            case TK_ASSIGNOP:
                printf("ASSIGN: %s\n", token.lexeme);
                break;
            case TK_COMMENT:
                printf("Comment: %s\n", token.lexeme);
                break;
            case TK_SQL:
                printf("SQL: %s\n", token.lexeme);
                break;
            case TK_SQR:
                printf("SQR: %s\n", token.lexeme);
                break;
            case TK_UNKNOWN:
                printf("Unknown: %s\n", token.lexeme);
                break;
        }
    } while (token.type != TK_END);

    fclose(fp);
    return 0;
}