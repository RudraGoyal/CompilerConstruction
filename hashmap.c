#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TSIZE 1000
struct hashNode
{
    char *key;
    int val;
    struct hashNode *next;
};
struct hashTable
{
    int currSize;
    int totalSize;
    struct hashNode *table[TSIZE];
};
typedef struct hashNode hashNode;
typedef struct hashTable hashmap;

hashNode *inithashNode(char *key, int val)
{
    hashNode *node = (hashNode *)malloc(sizeof(hashNode));
    node->key = (char *)malloc(strlen(key));
    strcpy(node->key, key);
    // node->key=key;
    node->val = val;
    node->next = NULL;
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
    return (abs(hash) % TSIZE);
}
int lookup(char *key, hashmap *map)
{
    // returns NULL if not found else returns the token
    int index = Jenkins_one_at_a_time_hashing_function(key);
    hashNode *head = map->table[index];
    while (head != NULL)
    {
        if (strcmp(head->key, key) == 0)
        {
            return head->val;
        }
        head = head->next;
    }
    return -1;
}

void insert(char *key, int val, hashmap *map)
{
    int index = Jenkins_one_at_a_time_hashing_function(key);
    hashNode *node = inithashNode(key, val);
    if (lookup(key, map) != -1)
        return;
    if (map->table[index] == NULL)
    {
        map->table[index] = node;
    }
    else
    {
        node->next = map->table[index];
        map->table[index] = node;
    }
    map->currSize++;
}

hashmap *inithashmap()
{
    hashmap *map = (hashmap *)malloc(sizeof(hashmap));
    map->currSize = 0;
    map->totalSize = TSIZE;
    for (int i = 0; i < TSIZE; i++)
    {
        map->table[i] = NULL;
    }

    return map;
}
// int main()
// {
// 	hashmap*symT= inithashTable();
//     insert("<---",2,symT);
//     insert(";",5,symT);
//     printf("%d\n",lookup("<---",symT));
//     printf("%d\n",lookup("hdjlashfldkja",symT));
//     printf("%d\n",lookup(";",symT));
// 	return 0;
// }
