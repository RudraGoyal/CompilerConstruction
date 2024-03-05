#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "parseTree.c"

int size_stack=200;
struct stackEntry{
    char*str;
    parseTreeNode* node;
    int bool;
};
typedef struct stackEntry stackEntry;
struct stack{
    stackEntry**stackptr; 
    int top;
};
typedef struct stack stack;

stack*initStack(){
    stack*st=(stack*)malloc(sizeof(stack));
    st->stackptr = (stackEntry**)malloc(sizeof(stackEntry*)*size_stack);
    st->top=-1;
    return st;
}
void iffull(stack*st){
    // printf("ifful called\n");
    size_stack*=2;
    st->stackptr=(stackEntry**)realloc(st->stackptr,sizeof(stackEntry*)*size_stack);
}
void push(stack*st,char*string, int bool, parseTreeNode*n){
    stackEntry*entry=(stackEntry*)malloc(sizeof(stackEntry));
    entry->bool=bool;
    entry->str=string;
    entry->node=n;
    if(st->top>=size_stack-1) iffull(st);
    st->top++;
    st->stackptr[st->top]=entry;
}
void pop(stack*st){
    if(st->top==-1) printf("Stack is Empty");
    else free(st->stackptr[st->top]),st->top--;
}
stackEntry*peek(stack*st){
    if(st->top==-1){
        return NULL;
    } 
    return st->stackptr[st->top];
}
int cap(stack*st){
    return st->top+1;
}
// int main(){
//     stack*st=initStack();
//     push(st,"<program>",0);
//     push(st,"b22bcd",1);
//     stackEntry*entry=peek(st);
//     printf("top ele %d --- %s \n",entry->bool,entry->str);
//     pop(st);
//     entry=peek(st);
//     printf("top ele %d --- %s\n",entry->bool,entry->str);
//     pop(st); pop(st);

// }