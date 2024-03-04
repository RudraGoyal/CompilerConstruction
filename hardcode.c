#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "stack.c"
#include "hashmap.c"
#include "lexer1.c"

int tokens=6;
int max_gram_len=3;
int line_no=8;

typedef struct first_follow_node{
    char*token;
    struct first_follow_node*next;
} first_follow_node;

void populate_node(first_follow_node*n1,char*value){
    n1->token=(char*)malloc(sizeof(char)*(strlen(value)+1));
    strcpy(n1->token,value);
    n1->next=NULL;
}

void firstAdder(first_follow_node**firstArr,char*val,int k){
    first_follow_node*node1=(first_follow_node*)malloc(sizeof(first_follow_node));
    populate_node(node1,val);
    node1->next=firstArr[k];
    firstArr[k]=node1;
}


void printParseTree(parseTreeNode*root,FILE*outline){
    // add file handle later
    parseTreeNode*p=root->childHead;
    while(p!=NULL && p->next!=NULL){
        printParseTree(p,outline);
        p=p->next;
    }
    if(root->isLeafNode==1)
    fprintf(outline,"%s          %d          %s          %s          %s          %s          %s\n",root->lexeme,root->line_no,root->token_name,root->value,root->parent->nodeSymbol,"yes",root->nodeSymbol);
    else fprintf(outline,"%s          %d          %s          %s          %s          %s          %s\n",root->lexeme,root->line_no,root->token_name,root->value,root->parent->nodeSymbol,"no",root->nodeSymbol);
    if(p!=NULL) printParseTree(p,outline);
}


void parser(stack*st,char*parseT[][tokens][max_gram_len],char**inp, hashmap*h1,hashmap*h2,hashmap*terminals)
{
    int inpptr=0;
    while(inpptr<6 && cap(st)>0){
    stackEntry*entry=peek(st);
    char*input=inp[inpptr];
    if(entry->bool==0){
        if(strcmp(entry->str,input)==0){
            printf("%s ",input);
            inpptr++;
            pop(st);
        }
        else {
            printf("ERROR\n");
            // call error routine
        }
    }
    else{
        int a=lookup(entry->str,h1);
        int b=lookup(input,h2);
        int k=0;
        parseTreeNode*parent=entry->node;
        printf("%s \n",entry->str);
        pop(st);
        // printf("a=%d  b=%d\n",a,b);
        while(k<3 && (parseT[a][b][k]!=NULL) && (strcmp(parseT[a][b][k],"ERROR")!=0)){
                if(lookup(parseT[a][b][k],terminals)==-1){
                    parseTreeNode*n1=initParseTreeNode("----",line_no,NULL,NULL,parent,parseT[a][b][k],0);
                    push(st,parseT[a][b][k],1,n1); // non terminal and terminal is an issue here so use symbol table
                    n1->next=parent->childHead;
                    parent->childHead=n1;
                }
                
                else{
                    // do remember to put symbol table instance as its not showing error
                    parseTreeNode*n2=initParseTreeNode(input,line_no,input,input,parent,NULL,1);
                    push(st,parseT[a][b][k],0,n2);
                    n2->next=parent->childHead;
                    parent->childHead=n2;
                } 
                printf("%s \t",parseT[a][b][k]);
            k++;
        }
        printf("\n");
        if(parseT[a][b][k]==NULL) k++;
        // printf("out of in while\n");
        if(k==0){
            printf("ERROR\n");
            // error routine
        }
    }
    }

}

int main(){
    char*parseT[53][57][6];
    for(int i=0;i<53;i++){
        for(int j=0;j<57;j++){
            for(int k=0;k<6;k++)
            parseT[i][j][k]="ERROR";
        }
    }
    hashmap*h1=inithashmap(); // non terminals
    insert("<program>", 0, h1);
    insert("<otherFunctions>", 1, h1);
    insert("<mainFunction>", 2, h1);
    insert("<stmts>", 3, h1);
    insert("<function>", 4, h1);
    insert("<input_par>", 5, h1);
    insert("<output_par>", 6, h1);
    insert("<parameter_list>", 7, h1);
    insert("<dataType>", 8, h1);
    insert("<remaining_list>", 9, h1);
    insert("<primitiveDatatype>", 10, h1);
    insert("<constructedDatatype>", 11, h1);
    insert("<typeDefinitions>", 12, h1);
    insert("<declarations>", 13, h1);
    insert("<otherStmts>", 14, h1);
    insert("<returnStmt>", 15, h1);
    insert("<actualOrRedefined>", 16, h1);
    insert("<typeDefinition>", 17, h1);
    insert("<definetypestmt>", 18, h1);
    insert("<fieldDefinitions>", 19, h1);
    insert("<fieldDefinition>", 20, h1);
    insert("<moreFields>", 21, h1);
    insert("<fieldtype>", 22, h1);
    insert("<declaration>", 23, h1);
    insert("<global_or_not>", 24, h1);
    insert("<stmt>", 25, h1);
    insert("<assignmentStmt>", 26, h1);
    insert("<iterativeStmt>", 27, h1);
    insert("<conditionalStmt>", 28, h1);
    insert("<ioStmt>", 29, h1);
    insert("<funCallStmt>", 30, h1);
    insert("<singleOrRecId>", 31, h1);
    insert("<arithmeticExpression>", 32, h1);
    insert("<SorRecHelper>", 33, h1);
    insert("<oneExpansion>", 34, h1);
    insert("<moreExpansions>", 35, h1);
    insert("<outputParameters>", 36, h1);
    insert("<inputParameters>", 37, h1);
    insert("<idList>", 38, h1);
    insert("<booleanExpression>", 39, h1);
    insert("<elsePart>", 40, h1);
    insert("<var>", 41, h1);
    insert("<term>", 42, h1);
    insert("<expPrime>", 43, h1);
    insert("<lowPrecedenceOperators>", 44, h1);
    insert("<factor>", 45, h1);
    insert("<termPrime>", 46, h1);
    insert("<highPrecedenceOperators>", 47, h1);
    insert("<logicalOp>", 48, h1);
    insert("<relationalOp>", 49, h1);
    insert("<optionalReturn>", 50, h1);
    insert("<more_ids>", 51, h1);
    insert("<A>", 52, h1);

    hashmap*h2=inithashmap(); // terminals + $
    insert("TK_MAIN", 0, h2);
    insert("TK_END", 1, h2);
    insert("eps", 2, h2);
    insert("TK_FUNID", 3, h2);
    insert("TK_SEM", 4, h2);
    insert("TK_INPUT", 5, h2);
    insert("TK_PARAMETER", 6, h2);
    insert("TK_LIST", 7, h2);
    insert("TK_SQL", 8, h2);
    insert("TK_SQR", 9, h2);
    insert("TK_OUTPUT", 10, h2);
    insert("TK_ID", 11, h2);
    insert("TK_INT", 12, h2);
    insert("TK_REAL", 13, h2);
    insert("TK_RECORD", 14, h2);
    insert("TK_RUID", 15, h2);
    insert("TK_UNION", 16, h2);
    insert("TK_COMMA", 17, h2);
    insert("TK_ENDRECORD", 18, h2);
    insert("TK_ENDUNION", 19, h2);
    insert("TK_TYPE", 20, h2);
    insert("TK_COLON", 21, h2);
    insert("TK_FIELDID", 22, h2);
    insert("TK_GLOBAL", 23, h2);
    insert("TK_ASSIGNOP", 24, h2);
    insert("TK_DOT", 25, h2);
    insert("TK_CALL", 26, h2);
    insert("TK_WITH", 27, h2);
    insert("TK_PARAMETERS", 28, h2);
    insert("TK_WHILE", 29, h2);
    insert("TK_OP", 30, h2);
    insert("TK_CL", 31, h2);
    insert("TK_ENDWHILE", 32, h2);
    insert("TK_IF", 33, h2);
    insert("TK_THEN", 34, h2);
    insert("TK_ELSE", 35, h2);
    insert("TK_ENDIF", 36, h2);
    insert("TK_READ", 37, h2);
    insert("TK_WRITE", 38, h2);
    insert("TK_MUL", 39, h2);
    insert("TK_DIV", 40, h2);
    insert("TK_PLUS", 41, h2);
    insert("TK_MINUS", 42, h2);
    insert("TK_NOT", 43, h2);
    insert("TK_NUM", 44, h2);
    insert("TK_RNUM", 45, h2);
    insert("TK_AND", 46, h2);
    insert("TK_OR", 47, h2);
    insert("TK_LT", 48, h2);
    insert("TK_LE", 49, h2);
    insert("TK_EQ", 50, h2);
    insert("TK_GT", 51, h2);
    insert("TK_GE", 52, h2);
    insert("TK_NE", 53, h2);
    insert("TK_RETURN", 54, h2);
    insert("TK_DEFINETYPE", 55, h2);
    insert("TK_AS", 56, h2);
    insert("$",57,h2);

    hashmap*terminals=inithashmap();
    insert("id",0,terminals);
    insert("+",0,terminals);
    insert("*",0,terminals);
    insert(")",0,terminals);
    insert("(",0,terminals);

    // parseT[0][0][0]="<otherFunctions>"; parseT[0][0][1]="<mainFunction>";
    // parseT[0][3][0]="<otherFunctions>"; parseT[0][3][1]="<mainFunction>";
    // parseT[1][3][0]="<otherFunctions>"; parseT[1][3][1]="<mainFunction>";
    // parseT[1][0][0]=NULL;

    first_follow_node**firstArr=(first_follow_node**)malloc(sizeof(first_follow_node*)*53);
    first_follow_node**followArr=(first_follow_node**)malloc(sizeof(first_follow_node*)*53);

    for(int i=0;i<53;i++){
        firstArr[i]=NULL;
        followArr[i]=NULL;
    }

    // first_follow_node*node1=(first_follow_node*)malloc(sizeof(first_follow_node));
    // populate_node(node1,"TK_MAIN");
    // node1->next=firstArr[0];
    // firstArr[0]=node1;
    firstAdder(firstArr, "TK_MAIN", 0);
    firstAdder(firstArr, "eps", 0);
    firstAdder(firstArr, "TK_FUNID", 0);
    firstAdder(firstArr, "TK_FUNID", 1);
    firstAdder(firstArr, "eps", 1);
    firstAdder(firstArr, "TK_MAIN", 2);
    firstAdder(firstArr, "TK_RETURN", 3);
    firstAdder(firstArr, "eps", 3);
    firstAdder(firstArr, "TK_ID", 3);
    firstAdder(firstArr, "TK_WHILE", 3);
    firstAdder(firstArr, "TK_IF", 3);
    firstAdder(firstArr, "TK_WRITE", 3);
    firstAdder(firstArr, "TK_READ", 3);
    firstAdder(firstArr, "TK_SQL", 3);
    firstAdder(firstArr, "eps", 3);
    firstAdder(firstArr, "TK_CALL", 3);
    firstAdder(firstArr, "eps", 3);
    firstAdder(firstArr, "TK_TYPE", 3);
    firstAdder(firstArr, "eps", 3);
    firstAdder(firstArr, "TK_UNION", 3);
    firstAdder(firstArr, "TK_RECORD", 3);
    firstAdder(firstArr, "TK_DEFINETYPE", 3);
    firstAdder(firstArr, "TK_FUNID", 4);
    firstAdder(firstArr, "TK_INPUT", 5);
    firstAdder(firstArr, "TK_OUTPUT", 6);
    firstAdder(firstArr, "eps", 6);
    firstAdder(firstArr, "TK_RECORD", 7);
    firstAdder(firstArr, "TK_UNION", 7);
    firstAdder(firstArr, "TK_RUID", 7);
    firstAdder(firstArr, "TK_INT", 7);
    firstAdder(firstArr, "TK_REAL", 7);
    firstAdder(firstArr, "TK_REAL", 8);
    firstAdder(firstArr, "TK_INT", 8);
    firstAdder(firstArr, "TK_RUID", 8);
    firstAdder(firstArr, "TK_UNION", 8);
    firstAdder(firstArr, "TK_RECORD", 8);
    firstAdder(firstArr, "eps", 9);
    firstAdder(firstArr, "TK_INT", 10);
    firstAdder(firstArr, "TK_REAL", 10);
    firstAdder(firstArr, "TK_RECORD", 11);
    firstAdder(firstArr, "TK_UNION", 11);
    firstAdder(firstArr, "TK_RUID", 11);
    firstAdder(firstArr, "TK_DEFINETYPE", 12);
    firstAdder(firstArr, "TK_RECORD", 12);
    firstAdder(firstArr, "TK_UNION", 12);
    firstAdder(firstArr, "eps", 12);
    firstAdder(firstArr, "TK_TYPE", 13);
    firstAdder(firstArr, "eps", 13);
    firstAdder(firstArr, "TK_CALL", 14);
    firstAdder(firstArr, "eps", 14);
    firstAdder(firstArr, "TK_SQL", 14);
    firstAdder(firstArr, "TK_READ", 14);
    firstAdder(firstArr, "TK_WRITE", 14);
    firstAdder(firstArr, "TK_IF", 14);
    firstAdder(firstArr, "TK_WHILE", 14);
    firstAdder(firstArr, "TK_ID", 14);
    firstAdder(firstArr, "eps", 14);
    firstAdder(firstArr, "TK_RETURN", 15);
    firstAdder(firstArr, "TK_UNION", 16);
    firstAdder(firstArr, "TK_RECORD", 16);
    firstAdder(firstArr, "TK_DEFINETYPE", 16);
    firstAdder(firstArr, "TK_RECORD", 17);
    firstAdder(firstArr, "TK_UNION", 17);
    firstAdder(firstArr, "TK_DEFINETYPE", 18);
    firstAdder(firstArr, "TK_RECORD", 19);
    firstAdder(firstArr, "TK_UNION", 19);
    firstAdder(firstArr, "TK_TYPE", 19);
    firstAdder(firstArr, "TK_TYPE", 20);
    firstAdder(firstArr, "TK_UNION", 20);
    firstAdder(firstArr, "TK_RECORD", 20);
    firstAdder(firstArr, "TK_RECORD", 21);
    firstAdder(firstArr, "TK_UNION", 21);
    firstAdder(firstArr, "TK_TYPE", 21);
    firstAdder(firstArr, "eps", 21);
    firstAdder(firstArr, "TK_REAL", 22);
    firstAdder(firstArr, "TK_INT", 22);
    firstAdder(firstArr, "TK_RUID", 22);
    firstAdder(firstArr, "TK_UNION", 22);
    firstAdder(firstArr, "TK_RECORD", 22);
    firstAdder(firstArr, "TK_TYPE", 23);
    firstAdder(firstArr, "eps", 24);
    firstAdder(firstArr, "TK_ID", 25);
    firstAdder(firstArr, "TK_WHILE", 25);
    firstAdder(firstArr, "TK_IF", 25);
    firstAdder(firstArr, "TK_WRITE", 25);
    firstAdder(firstArr, "TK_READ", 25);
    firstAdder(firstArr, "TK_SQL", 25);
    firstAdder(firstArr, "eps", 25);
    firstAdder(firstArr, "TK_CALL", 25);
    firstAdder(firstArr, "TK_ID", 26);
    firstAdder(firstArr, "TK_WHILE", 27);
    firstAdder(firstArr, "TK_IF", 28);
    firstAdder(firstArr, "TK_READ", 29);
    firstAdder(firstArr, "TK_WRITE", 29);
    firstAdder(firstArr, "TK_CALL", 30);
    firstAdder(firstArr, "eps", 30);
    firstAdder(firstArr, "TK_SQL", 30);
    firstAdder(firstArr, "TK_ID", 31);
    firstAdder(firstArr, "TK_OP", 32);
    firstAdder(firstArr, "TK_RNUM", 32);
    firstAdder(firstArr, "TK_NUM", 32);
    firstAdder(firstArr, "TK_ID", 32);
    firstAdder(firstArr, "eps", 33);
    firstAdder(firstArr, "TK_DOT", 33);
    firstAdder(firstArr, "TK_DOT", 34);
    firstAdder(firstArr, "TK_DOT", 35);
    firstAdder(firstArr, "eps", 36);
    firstAdder(firstArr, "TK_SQL", 37);
    firstAdder(firstArr, "TK_ID", 38);
    firstAdder(firstArr, "TK_OP", 39);
    firstAdder(firstArr, "TK_RNUM", 39);
    firstAdder(firstArr, "TK_NUM", 39);
    firstAdder(firstArr, "TK_ID", 39);
    firstAdder(firstArr, "TK_NOT", 39);
    firstAdder(firstArr, "TK_ELSE", 40);
    firstAdder(firstArr, "TK_ENDIF", 40);
    firstAdder(firstArr, "TK_ID", 41);
    firstAdder(firstArr, "TK_NUM", 41);
    firstAdder(firstArr, "TK_RNUM", 41);
    firstAdder(firstArr, "TK_ID", 42);
    firstAdder(firstArr, "TK_NUM", 42);
    firstAdder(firstArr, "TK_RNUM", 42);
    firstAdder(firstArr, "TK_OP", 42);
    firstAdder(firstArr, "TK_MINUS", 43);
    firstAdder(firstArr, "TK_PLUS", 43);
    firstAdder(firstArr, "eps", 43);
    firstAdder(firstArr, "TK_PLUS", 44);
    firstAdder(firstArr, "TK_MINUS", 44);
    firstAdder(firstArr, "TK_OP", 45);
    firstAdder(firstArr, "TK_RNUM", 45);
    firstAdder(firstArr, "TK_NUM", 45);
    firstAdder(firstArr, "TK_ID", 45);
    firstAdder(firstArr, "TK_DIV", 46);
    firstAdder(firstArr, "TK_MUL", 46);
    firstAdder(firstArr, "eps", 46);
    firstAdder(firstArr, "TK_MUL", 47);
    firstAdder(firstArr, "TK_DIV", 47);
    firstAdder(firstArr, "TK_AND", 48);
    firstAdder(firstArr, "TK_OR", 48);
    firstAdder(firstArr, "TK_LT", 49);
    firstAdder(firstArr, "TK_LE", 49);
    firstAdder(firstArr, "TK_EQ", 49);
    firstAdder(firstArr, "TK_GT", 49);
    firstAdder(firstArr, "TK_GE", 49);
    firstAdder(firstArr, "TK_NE", 49);
    firstAdder(firstArr, "TK_SQL", 50);
    firstAdder(firstArr, "eps", 50);
    firstAdder(firstArr, "TK_COMMA", 51);
    firstAdder(firstArr, "eps", 51);
    firstAdder(firstArr, "TK_RECORD", 52);
    firstAdder(firstArr, "TK_UNION", 52);

    


    // char*inp[6];
    // inp[0]="id";
    // inp[1]="+";
    // inp[2]="id"; inp[3]="*"; inp[4]="id"; inp[5]="$";
    // stack*st=initStack();

    // push(st,"$",0,NULL);
    // parseTreeNode*root1=initParseTreeNode(NULL,-1,NULL,NULL, NULL,"ROOT",0);
    // parseTreeNode*root=initParseTreeNode("----",0,NULL,NULL,root1,"E",0);
    // push(st,"E",1,root);
    // // printf("%s\n",parseT[0][0][0]);
    // // lex_header*input=(lex_header*)malloc(sizeof(lex_header));
    // // FILE*foo=fopen("text.txt","r");
    // // symTable* map=initsymbolTable();
    // // print(foo,map,input);

    // symTable* map=initsymbolTable();
    // lex_header* input=create_Larray();
    // fp = fopen("text.txt", "r");
    // getStream(fp);
    // print(fp,map,input);

    // for(int i=0;i<input->size;i++){
    //     printf("%s      %d      %s\n",input->arr[i]->lexe,input->arr[i]->line_no,input->arr[i]->token);
    // }
    // parser(st,parseT,(char**)inp,h1,h2,terminals);
    // // 1 non terminal 0 terminal
    // printf("\n");
    // FILE*fptr = fopen("parseTreeOutput.txt", "w");
    // printParseTree(root,fptr);
    for(int i=0;i<53;i++){
    first_follow_node*temp;
    temp=firstArr[i];
    while(temp){
    printf("%s  ",temp->token);
    temp=temp->next;
    }
    printf("\n");
    }

}