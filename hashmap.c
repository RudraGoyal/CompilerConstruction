#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define TSIZE 1000
struct bucketNode{
    char*key;
    int val;
    struct bucketNode*next;
};
struct symbolTable{
    int currSize;
    int totalSize;
    struct bucketNode* table[TSIZE];
};
typedef struct bucketNode bucketNode;
typedef struct symbolTable hashmap;


bucketNode* initbucketNode(char*key, int val){
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
int lookup(char* key, hashmap* map){
    // returns NULL if not found else returns the token
    int index=Jenkins_one_at_a_time_hashing_function(key);
    bucketNode*head= map->table[index];
    while(head!=NULL){
        if(strcmp(head->key, key)==0){
            return head->val;
        }
        head=head->next;
    }
    return -1;
}

void insert(char* key, int val, hashmap*map){
    int index=Jenkins_one_at_a_time_hashing_function(key);
    bucketNode*node= initbucketNode(key, val);
    if(lookup(key,map)!=-1) return;
    if(map->table[index]==NULL){
        map->table[index]=node;
    }
    else{
        node->next=map->table[index];
        map->table[index]=node;
    }
    map->currSize++;
}

hashmap* inithashmap(){
    hashmap* map=(hashmap*)malloc(sizeof(hashmap));
    map->currSize=0;
    map->totalSize=TSIZE;
    for(int i=0;i<TSIZE;i++){
        map->table[i]=NULL;
    }

    return map;
}
// int main()
// {	
// 	hashmap*symT= initsymbolTable();
//     insert("<---",2,symT);
//     insert(";",5,symT);
//     printf("%d\n",lookup("<---",symT));
//     printf("%d\n",lookup("hdjlashfldkja",symT));
//     printf("%d\n",lookup(";",symT));
// 	return 0;
// }



