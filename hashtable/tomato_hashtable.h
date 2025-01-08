#pragma once
#define BUCKETS 63
#include <stdbool.h>

typedef struct Node {
    int key;
    void *value;
    struct Node *next;
} Node;
typedef struct LinkedList {
    Node *head;
    Node *end;
} LinkedList;
typedef struct HashTable {
    LinkedList buckets[BUCKETS];
} HashTable;

HashTable hashtable_new();
void hashtable_free(HashTable* table);
void hashtable_add(HashTable* table, int key, void* value);
int hashtable_delete(HashTable* table, int key);
bool hashtable_size(HashTable* table);
bool hashtable_find(HashTable* table, int key, void* value);
void *hashtable_get(HashTable* table, int key);
void hashtable_print(HashTable* table);