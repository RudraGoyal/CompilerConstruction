#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int size=200;
struct parseTreeNode{
    char*lexeme;
    int line_no;
    char*token_name;
    double value; // used if its a number
    struct parseTreeNode*parent;
    int isLeafNode;
    char*nodeSymbol; // if not a terminal or leaf node
    struct parseTreeNode*childHead;
    struct parseTreeNode*next;
};
typedef struct parseTreeNode parseTreeNode;

parseTreeNode*initParseTreeNode(char*lexeme,int line_no,char*token_name,float value,parseTreeNode*parent,char*nodeSym,int isLeaf){
    parseTreeNode*n1=(parseTreeNode*)malloc(sizeof(parseTreeNode));
    n1->lexeme=lexeme;
    n1->isLeafNode=isLeaf;
    n1->line_no=line_no;
    n1->nodeSymbol=nodeSym;
    n1->parent=parent;
    n1->token_name=token_name;
    n1->value=value;
    n1->childHead=NULL;
    n1->next=NULL;
}
