#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "stack.c"
#include "hashmap.c"
#include "lexer.h"

int tokens=6;
int max_gram_len=3;
int line_no=8;


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
    char*parseT[5][6][3];
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            for(int k=0;k<3;k++)
            parseT[i][j][k]="ERROR";
        }
    }
    hashmap*h1=inithashmap();
    insert("E",0,h1);
    insert("E'",1,h1);
    insert("T",2,h1);
    insert("T'",3,h1);
    insert("F",4,h1);
    hashmap*h2=inithashmap();
    insert("id",0,h2);
    insert("+",1,h2);
    insert("*",2,h2);
    insert("(",3,h2);
    insert(")",4,h2);
    insert("$",5,h2);
    hashmap*terminals=inithashmap();
    insert("id",0,terminals);
    insert("+",0,terminals);
    insert("*",0,terminals);
    insert(")",0,terminals);
    insert("(",0,terminals);

    // printf("%s\n",parseT[0][0][0]);
    parseT[0][3][0]=parseT[0][0][0]="E'"; parseT[0][3][1]=parseT[0][0][1]="T";
    parseT[1][1][0]="E'"; parseT[1][1][1]="T"; parseT[1][1][2]="+";
    parseT[1][4][0]=parseT[1][5][0]=NULL;
    parseT[2][0][0]=parseT[2][3][0]="T'"; parseT[2][0][1]=parseT[2][3][1]="F";
    parseT[3][2][0]="T'"; parseT[3][2][1]="F"; parseT[3][2][2]="*";
    parseT[3][1][0]=parseT[3][4][0]=parseT[3][5][0]=NULL;
    parseT[4][0][0]="id"; 
    parseT[4][3][0]=")"; parseT[4][3][1]="E"; parseT[4][3][2]="(";
    char*inp[6];
    inp[0]="id";
    inp[1]="+";
    inp[2]="id"; inp[3]="*"; inp[4]="id"; inp[5]="$";
    stack*st=initStack();

    push(st,"$",0,NULL);
    parseTreeNode*root1=initParseTreeNode(NULL,-1,NULL,NULL, NULL,"ROOT",0);
    parseTreeNode*root=initParseTreeNode("----",0,NULL,NULL,root1,"E",0);
    push(st,"E",1,root);
    // printf("%s\n",parseT[0][0][0]);
    // lex_header*input=(lex_header*)malloc(sizeof(lex_header));
    // FILE*foo=fopen("text.txt","r");
    // symTable* map=initsymbolTable();
    // print(foo,map,input);

    symTable* map=initsymbolTable();
    lex_header* input=create_Larray();
    fp = fopen("text.txt", "r");
    getStream(fp);
    print(fp,map,input);

    for(int i=0;i<input->size;i++){
        printf("%s      %d      %s\n",input->arr[i]->lexe,input->arr[i]->line_no,input->arr[i]->token);
    }
    parser(st,parseT,(char**)inp,h1,h2,terminals);
    // 1 non terminal 0 terminal
    printf("\n");
    FILE*fptr = fopen("parseTreeOutput.txt", "w");
    printParseTree(root,fptr);


}
