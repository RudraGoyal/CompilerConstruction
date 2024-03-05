#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "hashmap.c"
#define listsize 100

char LIST_terminals[100][100];
char  LIST_nonterminals[100][100];
int i_t=0;
int i_nt=0;
char delim[]=" \n";
struct lexeme{
char* lexeme;
};


struct list_of_lexemes
{
struct lexeme LEX;
struct list_of_lexemes* NEXT;
};

struct FIRST_SET
{
struct list_of_lexemes** LIST;
};

struct FIRST_SET* create_FIRST_SET()
{
struct FIRST_SET* FS = (struct FIRST_SET*)(malloc((sizeof(struct FIRST_SET))));
FS->LIST = (struct list_of_lexemes**)(malloc(sizeof(struct list_of_lexemes*)*i_nt));
return FS;
}

struct grammar_rule_node
{

struct lexeme* lex;
struct grammar_rule_node* next;
};

typedef struct grammar_rule_node grammar;

struct lexeme* create_lexeme(char* s)
{
struct lexeme* lex = (struct lexeme*)malloc(sizeof(struct lexeme));
lex->lexeme = (char*)malloc(sizeof(char)*strlen(s));
strcpy(lex->lexeme,s);
return lex;
}


struct grammar_rule_node* create_grammar_rule_node()
{
struct grammar_rule_node* p = (struct grammar_rule_node*)malloc(sizeof(struct grammar_rule_node));
p->next = NULL;
return p;
}

struct grammar_rule_node* create_grammar_rule (char* s, hashmap * hash_nterminals, hashmap* hash_terminals)
{

struct grammar_rule_node* GR = create_grammar_rule_node();
char* token = strtok(s, delim);
struct lexeme* ll = create_lexeme(token);
GR->lex = ll;
token = strtok(NULL,delim);
struct grammar_rule_node* temp = GR;
while(token != NULL)
{
if(strcmp(token,"===>") == 0)
{
token = strtok(NULL,delim);
continue;
}
if(token[strlen(token)-1] == '\n')
token[strlen(token)-1] = '\0';
struct grammar_rule_node* G = create_grammar_rule_node();
struct lexeme* l = create_lexeme(token);
G->lex = l;
temp->next = G;
temp = G;
if(token[0] == '<' && token[strlen(token)-1] == '>' && (lookup(token, hash_nterminals) == -1))
{
insert(token,i_nt,hash_nterminals);
// printf("%ld, %d , %d , %d \n", strlen(token), token[0] == '<' , token[strlen(token)-1] == '>', (lookup(token, hash_nterminals) == -1));
strcpy(LIST_nonterminals[i_nt++], token);
//printf("Nonterminal == %s \n", token);
}
else if((token[0] != '<' || token[strlen(token)-1] != '>') && lookup(token, hash_terminals) == -1)
{
insert(token,i_t,hash_terminals);
strcpy(LIST_terminals[i_t++], token);
// printf("%ld, %d , %d , %d \n", strlen(token), token[0] == '<' , token[strlen(token)-1] == '>', (lookup(token, hash_nterminals) == -1));
//printf("Terminal == %s \n", token);
}

token = strtok(NULL, delim);
}
return GR;

}

void print_grammar_rule(struct grammar_rule_node* rule)
{

struct grammar_rule_node* GR = rule;
while(GR!=NULL)
{
printf("%s ",GR->lex->lexeme);
GR = GR->next;
}
printf("\n");

}
struct GRAMMAR
{
struct grammar_rule_node** LIST;
hashmap * hash_nterminals, *hash_terminals;
int size;
} ;



struct GRAMMAR* create_grammar(FILE* F)
{
struct GRAMMAR* G = (struct GRAMMAR*)malloc(sizeof(struct GRAMMAR));
G->LIST = (struct grammar_rule_node**)malloc(sizeof(struct grammar_rule_node*)*listsize);
G->hash_terminals = inithashmap();
G->hash_nterminals = inithashmap();

int index = 0;
char str[1000];
while(fgets(str,1000, F) != NULL)
{
G->LIST[index] = create_grammar_rule(str, G->hash_nterminals, G->hash_terminals);
index++;
}
G->size = index;

return G;
}

struct containerNode{
    int index;
    struct containerNode*next;
};
typedef struct containerNode containerNode;

containerNode*fillNode(int ind){
    containerNode*n=(containerNode*)malloc(sizeof(containerNode));
    n->index=ind;
    n->next=NULL;
    return n;
}

containerNode**workOnGram(struct GRAMMAR*g,int non_terminals){
    containerNode**array=(containerNode**)malloc(sizeof(containerNode*)*non_terminals);
    for(int i=0;i<non_terminals;i++) array[i]=NULL;
    int num=g->size;
    for(int i=0;i<num;i++){
        grammar* head=g->LIST[i];
        while(head!=NULL){
            if(lookup(head->lex->lexeme,g->hash_nterminals)!=-1){
                // printf("yahan pahuncho\n");
                containerNode*node=fillNode(i);
                node->next=array[lookup(head->lex->lexeme,g->hash_nterminals)];
                array[lookup(head->lex->lexeme,g->hash_nterminals)]=node;
            }
            head=head->next;
        }

    }
    return array;
}

containerNode** workOnGramFirst(struct GRAMMAR*g,int non_terminals){
    containerNode**array=(containerNode**)malloc(sizeof(containerNode*)*non_terminals);
    for(int i=0;i<non_terminals;i++) array[i]=NULL;
    int num=g->size;
    for(int i=0;i<num;i++){
            grammar*head=g->LIST[i];
            if(lookup(head->lex->lexeme,g->hash_nterminals)!=-1){
                containerNode*node=fillNode(i);
                node->next=array[lookup(head->lex->lexeme,g->hash_nterminals)];
                array[lookup(head->lex->lexeme,g->hash_nterminals)]=node;
            }
    }
    return array;
}


// void populate_FS(struct GRAMMAR* GR)
// {
// int finished[i_nt];
// for(int i=0; i<i_nt; i++)
// {
// finished[i_nt] = -1;
// }

// int flag = 1;
// int i=0;
// while(flag)
// {
// flag = 0;
// for(int i=0; i<GR->size; i++)
// {
// if(finished[i] == -1)
// {

// }
// }
// if(finished[i] == -1)
// {
// flag = 1;
// }
// }
// }



int main()
{

char G_Rule[] = "<Aditya> ==> <A> TK_UNION <B> <C>";
FILE* F;
F = fopen("Grammar.txt", "r");
struct GRAMMAR* G = create_grammar(F);
containerNode** C = workOnGramFirst(G, i_t);
int size = G->size;
printf("%d \n", size);
for(int i=0; i<size; i++)
{
print_grammar_rule(G->LIST[i]);
}
printf(" \n \n \n TERMINALS : \n");
for(int i=0; i<i_t; i++)
{
printf("%s  %d \n", LIST_terminals[i],i);
}
printf("\n \n \n NON TERMINALS : \n");
for(int i=0; i<i_nt; i++)
{
printf("%s  %d \n", LIST_nonterminals[i],i);
}

for(int i=0; i<i_nt; i++)
{
containerNode* curr = C[i];
while(curr != NULL)
{
printf("%d ", curr->index);
curr = curr->next;
}

printf("\n");
}

return 0;
}