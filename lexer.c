#include "lexer.h"

TokenType getTokenType(const char* lexeme){
    if (!strcmp(lexeme, "<---")) 
        return TK_ASSIGNOP;
    else if (!strcmp(lexeme, "%%")) 
        return TK_COMMENT;
    else if (!strcmp(lexeme, "with")) 
        return TK_WITH;
    else if (!strcmp(lexeme, "parameters")) 
        return TK_PARAMETERS;
    else if (!strcmp(lexeme, "end")) 
        return TK_END;
    else if (!strcmp(lexeme, "while")) 
        return TK_WHILE;
    else if (!strcmp(lexeme, "union")) 
        return TK_UNION;
    else if (!strcmp(lexeme, "endunion")) 
        return TK_ENDUNION;
    else if (!strcmp(lexeme, "definetype")) 
        return TK_DEFINETYPE;
    else if (!strcmp(lexeme, "as")) 
        return TK_AS;
    else if (!strcmp(lexeme, "type")) 
        return TK_TYPE;
    else if (!strcmp(lexeme, "_main")) 
        return TK_MAIN;
    else if (!strcmp(lexeme, "global")) 
        return TK_GLOBAL;
    else if (!strcmp(lexeme, "parameter")) 
        return TK_PARAMETER;
    else if (!strcmp(lexeme, "list")) 
        return TK_LIST;
    else if (!strcmp(lexeme, "[")) 
        return TK_SQL;
    else if (!strcmp(lexeme, "]")) 
        return TK_SQR;
    else if (!strcmp(lexeme, "input")) 
        return TK_INPUT;
    else if (!strcmp(lexeme, "output")) 
        return TK_OUTPUT;
    else if (!strcmp(lexeme, "int")) 
        return TK_INT;
    else if (!strcmp(lexeme, "real")) 
        return TK_REAL;
    else if (!strcmp(lexeme, ",")) 
        return TK_COMMA;
    else if (!strcmp(lexeme, ";")) 
        return TK_SEM;
    else if (!strcmp(lexeme, ":")) 
        return TK_COLON;
    else if (!strcmp(lexeme, ".")) 
        return TK_DOT;
    else if (!strcmp(lexeme, "endwhile")) 
        return TK_ENDWHILE;
    else if (!strcmp(lexeme, "(")) 
        return TK_OP;
    else if (!strcmp(lexeme, ")")) 
        return TK_CL;
    else if (!strcmp(lexeme, "if")) 
        return TK_IF;
    else if (!strcmp(lexeme, "then")) 
        return TK_THEN;
    else if (!strcmp(lexeme, "endif")) 
        return TK_ENDIF;
    else if (!strcmp(lexeme, "read")) 
        return TK_READ;
    else if (!strcmp(lexeme, "write")) 
        return TK_WRITE;
    else if (!strcmp(lexeme, "return")) 
        return TK_RETURN;
    else if (!strcmp(lexeme, "+")) 
        return TK_PLUS;
    else if (!strcmp(lexeme, "-")) 
        return TK_MINUS;
    else if (!strcmp(lexeme, "*")) 
        return TK_MUL;
    else if (!strcmp(lexeme, "/")) 
        return TK_DIV;
    else if (!strcmp(lexeme, "call")) 
        return TK_CALL;
    else if (!strcmp(lexeme, "record")) 
        return TK_RECORD;
    else if (!strcmp(lexeme, "endrecord")) 
        return TK_ENDRECORD;
    else if (!strcmp(lexeme, "else")) 
        return TK_ELSE;
    else if (!strcmp(lexeme, "&&&")) 
        return TK_AND;
    else if (!strcmp(lexeme, "@@@")) 
        return TK_OR;
    else if (!strcmp(lexeme, "~")) 
        return TK_NOT;
    else if (!strcmp(lexeme, "<")) 
        return TK_LT;
    else if (!strcmp(lexeme, "<=")) 
        return TK_LE;
    else if (!strcmp(lexeme, "==")) 
        return TK_EQ;
    else if (!strcmp(lexeme, ">")) 
        return TK_GT;
    else if (!strcmp(lexeme, ">=")) 
        return TK_GE;
    else if (!strcmp(lexeme, "!=")) 
        return TK_NE;

}

Token getNextToken(FILE* fp, char buffer[][BUFFER_SIZE], int bufsize, int* bufferIndex) {
    Token token;
    token.type = TK_END;
    char lexeme[MAX_TOKEN_SIZE] = "";
    int lexemeIndex = 0;
    char c;

    while (1) {
        c = buffer[0][*bufferIndex];
        if (isspace(c) || c == '\0') {
            if (lexemeIndex > 0) {
                strncpy(token.lexeme, lexeme, lexemeIndex);
                token.lexeme[lexemeIndex] = '\0';
                // printf("%s\n",lexeme);
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

void printToken(Token token)
{
    switch (token.type){
    case TK_ASSIGNOP:
        printf("ASSIGN: %s\n", token.lexeme);
        break;
    case TK_COMMENT:
        printf("Comment: %s\n", token.lexeme);
        break;
    case TK_WITH:
        printf("WITH: %s\n", token.lexeme);
        break;
    case TK_PARAMETERS:
        printf("PARAMETERS: %s\n", token.lexeme);
        break;
    case TK_END:
        printf("END: %s\n", token.lexeme);
        break;
    case TK_WHILE:
        printf("WHILE: %s\n", token.lexeme);
        break;
    case TK_UNION:
        printf("UNION: %s\n", token.lexeme);
        break;
    case TK_ENDUNION:
        printf("ENDUNION: %s\n", token.lexeme);
        break;
    case TK_DEFINETYPE:
        printf("DEFINETYPE: %s\n", token.lexeme);
        break;
    case TK_AS:
        printf("AS: %s\n", token.lexeme);
        break;
    case TK_TYPE:
        printf("TYPE: %s\n", token.lexeme);
        break;
    case TK_MAIN:
        printf("MAIN: %s\n", token.lexeme);
        break;
    case TK_GLOBAL:
        printf("GLOBAL: %s\n", token.lexeme);
        break;
    case TK_PARAMETER:
        printf("PARAMETER: %s\n", token.lexeme);
        break;
    case TK_LIST:
        printf("LIST: %s\n", token.lexeme);
        break;
    case TK_SQL:
        printf("SQL: %s\n", token.lexeme);
        break;
    case TK_SQR:
        printf("SQR: %s\n", token.lexeme);
        break;
    case TK_INPUT:
        printf("INPUT: %s\n", token.lexeme);
        break;
    case TK_OUTPUT:
        printf("OUTPUT: %s\n", token.lexeme);
        break;
    case TK_INT:
        printf("INT: %s\n", token.lexeme);
        break;
    case TK_REAL:
        printf("REAL: %s\n", token.lexeme);
        break;
    case TK_COMMA:
        printf("COMMA: %s\n", token.lexeme);
        break;
    case TK_SEM:
        printf("SEM: %s\n", token.lexeme);
        break;
    case TK_COLON:
        printf("COLON: %s\n", token.lexeme);
        break;
    case TK_DOT:
        printf("DOT: %s\n", token.lexeme);
        break;
    case TK_ENDWHILE:
        printf("ENDWHILE: %s\n", token.lexeme);
        break;
    case TK_OP:
        printf("OP: %s\n", token.lexeme);
        break;
    case TK_CL:
        printf("CL: %s\n", token.lexeme);
        break;
    case TK_IF:
        printf("IF: %s\n", token.lexeme);
        break;
    case TK_THEN:
        printf("THEN: %s\n", token.lexeme);
        break;
    case TK_ENDIF:
        printf("ENDIF: %s\n", token.lexeme);
        break;
    case TK_READ:
        printf("READ: %s\n", token.lexeme);
        break;
    case TK_WRITE:
        printf("WRITE: %s\n", token.lexeme);
        break;
    case TK_RETURN:
        printf("RETURN: %s\n", token.lexeme);
        break;
    case TK_PLUS:
        printf("PLUS: %s\n", token.lexeme);
        break;
    case TK_MINUS:
        printf("MINUS: %s\n", token.lexeme);
        break;
    case TK_MUL:
        printf("MUL: %s\n", token.lexeme);
        break;
    case TK_DIV:
        printf("DIV: %s\n", token.lexeme);
        break;
    case TK_CALL:
        printf("CALL: %s\n", token.lexeme);
        break;
    case TK_RECORD:
        printf("RECORD: %s\n", token.lexeme);
        break;
    case TK_ENDRECORD:
        printf("ENDRECORD: %s\n", token.lexeme);
        break;
    case TK_ELSE:
        printf("ELSE: %s\n", token.lexeme);
        break;
    case TK_AND:
        printf("AND: %s\n", token.lexeme);
        break;
    case TK_OR:
        printf("OR: %s\n", token.lexeme);
        break;
    case TK_NOT:
        printf("NOT: %s\n", token.lexeme);
        break;
    case TK_LT:
        printf("LT: %s\n", token.lexeme);
        break;
    case TK_LE:
        printf("LE: %s\n", token.lexeme);
        break;
    case TK_EQ:
        printf("EQ: %s\n", token.lexeme);
        break;
    case TK_GT:
        printf("GT: %s\n", token.lexeme);
        break;
    case TK_GE:
        printf("GE: %s\n", token.lexeme);
        break;
    case TK_NE:
        printf("NE: %s\n", token.lexeme);
        break;
    case TK_UNKNOWN:
    default:
        printf("Unknown: %s\n", token.lexeme);
        break;
    }
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
    FILE* fp = fopen("./TestCases/t3.txt", "r");
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
        printToken(token);
        } while (token.type != TK_END);

    fclose(fp);
    return 0;
}