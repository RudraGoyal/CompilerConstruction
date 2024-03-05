#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

void concatenate_string(char* s,int j, char* s1)
{
    int i;
    for (i = 0; s1[i] != '\0'; i++) {
        s[i + j] = s1[i];
    }
    s[i + j] = '\0';
    return;
}

int isAlpha(char c)
{
    if(c>= 65 && c<= 90)
    return 1;
    else if(c>= 97 && c<=122)
    return 1;
    else 
    return 0;
}

#define BUFFERSIZE 100
FILE * fp;
char DoubleBuffer[2][BUFFERSIZE];
int p = 1; 
int preend=-1;
int readSize;
int merge = 0;
int Line_No = 1;
int getStream(FILE *fp)
{
    if(fp == NULL)
    {
        printf("Error /n");
        
    }
    if(p==1)
    {
       readSize=fread(DoubleBuffer[0], sizeof(char), BUFFERSIZE , fp);
        // printf("Buffer 1 filled \n");
        p = 0;
    }
    else 
    {
        readSize=fread(DoubleBuffer[1], sizeof(char), BUFFERSIZE, fp);
        // printf("Buffer 2 filled \n");
        p = 1;
    }
    
}

char read(int* end, FILE* fp)
{
    if(readSize<=1){ 
        readSize--;
        return '$';
    }
    
    if(readSize < BUFFERSIZE)
    {
        // readSize--;
        if(preend == -1){
            preend = *end;
            readSize--;
        }
        if(preend != *end){
            readSize--;
            preend= *end; 
        }
    }
    if(*end >= BUFFERSIZE)
    {
        *end = 0;
        getStream(fp);
        merge = 1;
    }
    
    // if(DoubleBuffer[p][*end] == '\n')
    // Line_No++;
    // printf(" {%d , %c} \n",readSize, DoubleBuffer[p][(*end)]);
    return DoubleBuffer[p][(*end)];

}

char* ret_lexeme_error(int beg, int end)
{
if(merge==1 && beg<=end) merge=0;
 if(Line_No>14) exit(0);
if(merge == 0)
{
    char* ans = (char*)malloc(sizeof(char)*(end-beg+2));
    strncpy(ans, DoubleBuffer[p]+beg, end-beg + 1);
    ans[end-beg+1] = '\0';
    //printf("%s --- %d \n", ans, Line_No);
    return ans;
}
else{
    // printf("issue %d && %d",beg,end);
    char* ans1 = (char*)malloc(sizeof(char)*(BUFFERSIZE-beg+1));
    char* ans = (char*)malloc(sizeof(char)*(BUFFERSIZE -beg+end+2));
    char* ans2 = (char*)malloc(sizeof(char)*(end+2));
    strncpy(ans1, DoubleBuffer[1-p]+beg, BUFFERSIZE-beg);
    strncpy(ans2, DoubleBuffer[p], end+1);
    ans2[end+1]='\0';
    ans1[BUFFERSIZE-beg]='\0';
    // char* ans = (char*)malloc(sizeof(char)*(BUFFERSIZE -beg+end+2));
    strncpy(ans,ans1,BUFFERSIZE-beg);
    concatenate_string(ans,BUFFERSIZE-beg,ans2);
    // printf("%s --- %d \n", ans, Line_No);
    merge=0;
    // printf("buffer issues end");
    return ans;
}
}



char* ret_lexeme(int beg, int end)
{
if(merge==1 && beg<=end) merge=0;
 if(Line_No>14) exit(0);
if(merge == 0)
{
    char* ans = (char*)malloc(sizeof(char)*(end-beg+2));
    strncpy(ans, DoubleBuffer[p]+beg, end-beg + 1);
    ans[end-beg+1] = '\0';
    printf("%s --- %d \n", ans, Line_No);
    return ans;
}
else{
    // printf("issue %d && %d",beg,end);
    char* ans1 = (char*)malloc(sizeof(char)*(BUFFERSIZE-beg+1));
    char* ans = (char*)malloc(sizeof(char)*(BUFFERSIZE -beg+end+2));
    char* ans2 = (char*)malloc(sizeof(char)*(end+2));
    strncpy(ans1, DoubleBuffer[1-p]+beg, BUFFERSIZE-beg);
    strncpy(ans2, DoubleBuffer[p], end+1);
    ans2[end+1]='\0';
    ans1[BUFFERSIZE-beg]='\0';
    // char* ans = (char*)malloc(sizeof(char)*(BUFFERSIZE -beg+end+2));
    strncpy(ans,ans1,BUFFERSIZE-beg);
    concatenate_string(ans,BUFFERSIZE-beg,ans2);
    printf("%s --- %d \n", ans, Line_No);
    merge=0;
    // printf("buffer issues end");
    return ans;
}
}

void print(FILE* fp)
{
    int beg=0;
    int end=0; 
    int t = 1;
    
    while(t)
    {
    // if(end>=BUFFERSIZE) end=0
    beg = end;
    char inp = read(&end, fp);
    if(isdigit(inp))
    {
        inp = '1';
    }
    else if(isAlpha(inp))
    {
        if(inp == 'b' || inp == 'c' || inp == 'd')
            inp = '2';
        else 
            inp = '3';
    }
    switch (inp)
    {
    case '!':
        end++;
        if(read(&end,fp) == '=')
        {
            printf("TK_NE "); 
            ret_lexeme(beg,end);
            end++;
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
        
        break;
    case '=':
        end++;
        if(read(&end,fp) == '=')
        {printf("TK_EQ "); ret_lexeme(beg,end); end++;}
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
        break;
    case '>':
        end++;
        if(read(&end,fp) == '=')
        {printf("TK_GE "); ret_lexeme(beg,end); end++;}
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
        break;
    case '@':
        end++;
        if(read(&end,fp) == '@')
        {
            end++;
            if(read(&end,fp) == '@')
            {
                printf("TK_OR ");     
                ret_lexeme(beg,end);
                end++;
                
            }
            else
            printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
    break;

    case '&':
        end++;
        if(read(&end,fp) == '&')
        {
            end++;
            if(read(&end,fp) == '&')
            {
                printf("TK_AND ");ret_lexeme(beg,end);
                end++;
                
            }
            else
            printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
    break;
    
    case '*':
        printf("TK_MUL ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '+':
        printf("TK_PLUS ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '~':
        printf("TK_NOT ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '/':
        printf("TK_DIV ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '.':
        printf("TK_DOT ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '-':
        printf("TK_MINUS ");
        ret_lexeme(beg,end);
        end++;
    break;

    case ':':
        printf("TK_COLON ");
        ret_lexeme(beg,end);
        end++;

    break;

    case ';':
        printf("TK_SEM ");
        ret_lexeme(beg,end);
        end++;
    break;

    case ',':
        printf("TK_COMMA ");
        ret_lexeme(beg,end);
        end++;
    break;

    case ')':
        printf("TK_CL ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '(':
        printf("TK_OP ");
        ret_lexeme(beg,end);
        end++;
    break;

    case ']':
        printf("TK_SQR ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '[':
        printf("TK_SQL ");
        ret_lexeme(beg,end);
        end++;
    break;

    case '%':
        printf("TK_COMMENT ");
        while(read(&end, fp) != '\n')
        end++;
        ret_lexeme(beg,end-1);
        
    break;

    case '#':
        end++;
        if(isAlpha(read(&end,fp)))
        {
            end++;
            while(isAlpha(read(&end,fp)))
                end++;
            printf("TK_RUID ");
            ret_lexeme(beg,end - 1);
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
    break;

    case '<':
        end++;
        if(read(&end,fp) == '=')
        {
            end++;
            printf("TK_LE ");
            ret_lexeme(beg,end-1);
        }
        else if(read(&end,fp) == '-')
        {
            end++;
            if(read(&end,fp) == '-')
            {
                end++;
                if(read(&end,fp) == '-')
                {
                    printf("TK_ASSIGNOP ");
                    ret_lexeme(beg,end);
                    end++;
                }
                else 
                {
                    printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
                }
            }
            else 
            {
                printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
            }
        }
        else 
        {
            printf("TK_LT ");
            ret_lexeme(beg,end-1);
        }
    break;

    case '_':
        end++;
        if(isAlpha(read(&end,fp)))
        {
            end++;
            while(isAlpha(read(&end,fp)))
                end++;
            while(isdigit(read(&end,fp)))
                end++;
            if(strlen(ret_lexeme_error(beg,end-1))>30) printf("Error: The length of function id lexeme given is greater than 30 --- %d\n",Line_No);
            else {
                printf("TK_FUNID ");
                ret_lexeme(beg,end-1);
            }
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
    break;

    case '1' :
    end++;
    while(isdigit(read(&end,fp)))
    end++;
    if(read(&end,fp) == '.')
    {
        end++;
        if(isdigit(read(&end,fp)))
        {
            end++;
            if(isdigit(read(&end,fp)))
            {
                end++;
                if(read(&end,fp) == 'E')
                {
                    end++;
                    if(read(&end,fp) == '+' || read(&end,fp) == '-')
                    {
                         end++;
                         if(isdigit(read(&end,fp)))
                            {
                                end++;
                                if(isdigit(read(&end,fp)))
                                {
                                    printf("TK_RNUM ");
                                    ret_lexeme(beg,end);
                                    end++;
                                }
                                else 
                                {
                                    printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
                                }
                            }

                    }
                    else if(isdigit(read(&end,fp)))
                    {
                        end++;
                        if(isdigit(read(&end,fp)))
                        {
                            printf("TK_RNUM ");
                            ret_lexeme(beg,end);
                            end++;
                        }
                        else 
                        {
                            printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
                        }
                    }
                    else 
                    {
                        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
                    }
                }
                else 
                {
                    printf("TK_RNUM ");
                    ret_lexeme(beg,end-1);
                }
            }
            else 
            {
                printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);
            }
        }
        else 
        printf("error  unrecognized pattern <%s> --- %d\n", ret_lexeme_error(beg,end-1), Line_No);

    }
    else 
    {
        printf("TK_NUM ");
        ret_lexeme(beg,end-1);
    }

    break;

    case '2':
    end++;
     char c = read(&end,fp);
    //  printf("%c",c);
    if(isAlpha(c))
    {
        end++;
        // printf("here");
        while(isAlpha(read(&end,fp)))
            end++;
        // if(strlen(ret_lexeme_error(beg,end-1))>20) printf("Error: The length of variable id lexeme given is greater than 20\n");
        // else 
        // {
            printf("LOOKUP ");
            ret_lexeme(beg,end-1);
        // }
    }
    else if( read(&end,fp) <= 55 && read(&end,fp) >=50)
    {
        // printf("lalu");
        end++;
        while( read(&end,fp) <= 100 && read(&end,fp) >= 98)
            end++;
        if(read(&end,fp) <= 55 && read(&end,fp) >=50)
        {
            end++;
            while(read(&end,fp) <= 55 && read(&end,fp) >=50)
                end++;
            if(strlen(ret_lexeme_error(beg,end-1))>20) printf("Error: The length of variable id lexeme given is greater than 20\n");
            else{ 
                printf("TK_ID ");
                ret_lexeme(beg,end-1);
            }
        }
        else 
        {   if(strlen(ret_lexeme_error(beg,end-1))>20) printf("Error: The length of variable id lexeme given is greater than 20\n");
            else{
                printf("TK_ID ");
                ret_lexeme(beg,end-1);
            }
        }
    }
    break;

    case '3':
    end++;
    if(isalpha(read(&end,fp)))
    {
        // printf("yahan ");
        end++;
        while(isalpha(read(&end,fp)))
            end++;
        // if(strlen(ret_lexeme_error(beg,end-1))>20) printf("Error:   The length of variable id lexeme given is greater than 20\n");
            printf("LOOKUP ");
            ret_lexeme(beg,end-1);
    }  
    break;
    
    case '\n':
    Line_No++;
    end++;
    break;

    case ' ':
    end++;
    break;

    case '$':
    if(readSize<=0) 
    t=0;
    else printf("Error Unrecognized Symbol <$> --- %d\n",Line_No);
    end++;
    break;

    // case '|':
    // end++;
    // break;

    default:
        printf("Error Unrecognized Symbol <%s> --- %d \n", ret_lexeme_error(beg,end), Line_No);
        // ret_lexeme(beg,end);
        end++;
        break;
    }
    }

}

int main()
{
    fp = fopen("text.txt", "r");
    getStream(fp);
    // printf("%s", DoubleBuffer[0]);
    print(fp);
    return 0;
}