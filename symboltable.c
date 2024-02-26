#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define TSIZE 1000
struct bucketNode{
    char*key;
    char*val;
    struct bucketNode*next;
};
struct symbolTable{
    int currSize;
    int totalSize;
    struct bucketNode* table[TSIZE];
};
typedef struct bucketNode bucketNode;
typedef struct symbolTable symTable;


bucketNode* initbucketNode(char*key, char*val){
    bucketNode*node=(bucketNode*)malloc(sizeof(bucketNode));
    node->key=key;
    node->val=val;
    node->next=NULL;
    return node;
}
int Jenkins_one_at_a_time_hashing_function(const char *str)
{
    int hash, i;
    for (hash = i = 0; str[i] != '\0'; i++)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (abs(hash)%TSIZE);
}
char* lookup(char* key, symTable* map){
    // returns NULL if not found else returns the token
    int index=Jenkins_one_at_a_time_hashing_function(key);
    bucketNode*head= map->table[index];
    while(head!=NULL){
        if(strcmp(head->key, key)==0){
            return head->val;
        }
        head=head->next;
    }
    return NULL;
}

void insert(char* key, char* val, symTable*map){
    int index=Jenkins_one_at_a_time_hashing_function(key);
    bucketNode*node= initbucketNode(key, val);
    if(lookup(key,map)!=NULL) return;
    if(map->table[index]==NULL){
        map->table[index]=node;
    }
    else{
        node->next=map->table[index];
        map->table[index]=node;
    }
    map->currSize++;
}

symTable* initsymbolTable(){
    symTable* map=(symTable*)malloc(sizeof(symTable));
    map->currSize=0;
    map->totalSize=TSIZE;
    for(int i=0;i<TSIZE;i++){
        map->table[i]=NULL;
    }
    insert("<---", "TK_ASSIGNOP", map);
    insert("%%", "TK_COMMENT", map);
    insert("with", "TK_WITH", map);
    insert("parameters", "TK_PARAMETERS", map);
    insert("end", "TK_END", map);
    insert("while", "TK_WHILE", map);
    insert("union", "TK_UNION", map);
    insert("endunion", "TK_ENDUNION", map);
    insert("definetype", "TK_DEFINETYPE", map);
    insert("as", "TK_AS", map);
    insert("type", "TK_TYPE", map);
    insert("_main", "TK_MAIN", map);
    insert("global", "TK_GLOBAL", map);
    insert("parameter", "TK_PARAMETER", map);
    insert("list", "TK_LIST", map);
    insert("[", "TK_SQL", map);
    insert("]", "TK_SQR", map);
    insert("input", "TK_INPUT", map);
    insert("output", "TK_OUTPUT", map);
    insert("int", "TK_INT", map);
    insert("real", "TK_REAL", map);
    insert(",", "TK_COMMA", map);
    insert(";", "TK_SEM", map);
    insert(":", "TK_COLON", map);
    insert(".", "TK_DOT", map);
    insert("endwhile", "TK_ENDWHILE", map);
    insert("(", "TK_OP", map);
    insert(")", "TK_CL", map);
    insert("if", "TK_IF", map);
    insert("then", "TK_THEN", map);
    insert("endif", "TK_ENDIF", map);
    insert("read", "TK_READ", map);
    insert("write", "TK_WRITE", map);
    insert("return", "TK_RETURN", map);
    insert("+", "TK_PLUS", map);
    insert("-", "TK_MINUS", map);
    insert("*", "TK_MUL", map);
    insert("/", "TK_DIV", map);
    insert("call", "TK_CALL", map);
    insert("record", "TK_RECORD", map);
    insert("endrecord", "TK_ENDRECORD", map);
    insert("else", "TK_ELSE", map);
    insert("&&&", "TK_AND", map);
    insert("@@@", "TK_OR", map);
    insert("~", "TK_NOT", map);
    insert("<", "TK_LT", map);
    insert("<=", "TK_LE", map);
    insert("==", "TK_EQ", map);
    insert(">", "TK_GT", map);
    insert(">=", "TK_GE", map);
    insert("!=", "TK_NE", map);

    return map;
}
int main()
{	
	symTable*symT= initsymbolTable();
    // insert("<---","TK_ASSIGNOP",symT);
    // insert(";","TK_SEM",symT);
    printf("%s\n",lookup(";",symT));
    printf("%s\n",lookup("hdjlashfldkja",symT));
    printf("%s\n",lookup("end",symT));



	return 0;
}



