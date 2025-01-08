 /*
The following is a closed address HashTable of key, value pairs
63 buckets
using a stupid modulo hashing function

Problems:
Am I supposed to free the values if you delete the pair?
Hashing function
Number of buckets
why can't i use names remove and delete?
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hashtable.h"

Node* new_list_element(int key, void* value, Node* ptr) {
    Node* new_node = malloc(sizeof(Node));
    new_node -> key = key;
    new_node -> value = value;
    new_node -> next = ptr;
    return new_node;
}
LinkedList* new_list() {
    LinkedList* list = malloc(sizeof(LinkedList));
    list -> head = NULL;
    list -> end = NULL;
    return list;
}
HashTable* hashtable_new() {
    HashTable* table = malloc(sizeof(HashTable));
    for(size_t i = 0; i < BUCKETS; i++) {
        table -> buckets[i] = new_list();
    }
    return table;
}
void hashtable_free(HashTable* table) {
    if(table == NULL) return;
    for(size_t i = 0; i < BUCKETS; i++) {
        LinkedList* list = table -> buckets[i];
        if(list == NULL) continue;
        Node* head = list->head;
        list -> head = NULL;
        list -> end = NULL;
        Node* previous;
        while(head != NULL){
            previous = head;
            head = head -> next;
            free(previous -> value);
            free(previous);
        }    
        free(list);
    }
    free(table);
}

unsigned int hash(int key) {
    return key % BUCKETS;
}

void hashtable_add(HashTable* table, int key, void* value) {
    LinkedList* list = table -> buckets[hash(key)];
    Node* new_node = new_list_element(key, value, list -> head);
    list -> head = new_node;
}

// bool hashtable_delete(HashTable* table, int key) {
//     LinkedList* list = table -> buckets[hash(key)];
//     Node* current = list -> head;
//     if(current == NULL) return false;
//     if(current -> key == key) {
//         if(current == list -> end) list -> end = NULL;
//         list -> head = current -> next;
//         free(current -> value);
//         free(current);
//         return true;
//     }
//     Node* previous;
//     while(current != NULL) {
//         if(current -> key == key) {
//             previous -> next = current -> next;
//             if(current == list -> end) list -> end = previous;
//             free(current -> value);
//             free(current);
//             return true;
//         }
//         previous = current;
//         current = current -> next;
//     }
//     return false;
// }

// int hashtable_size(HashTable* table) {
//     int size = 0;
//     for(size_t i = 0; i < BUCKETS; i++) {
//         Node* current = table -> buckets[i] -> head;
//         while(current != NULL) {
//             size++;
//             current = current -> next;
//         }
//     }
//     return size;
// }

// bool hashtable_find(HashTable* table, int key, void* value) {
//     Node* current = table -> buckets[hash(key)] -> head;
//     while(current != NULL) {
//         if(current -> key == key && current -> value == value) return true;
//         current = current -> next;
//     }
//     return false;
// }

// void* hashtable_get(HashTable* table, int key) {
//     Node* current = table -> buckets[hash(key)] -> head;
//     while(current != NULL) {
//         if(current -> key == key) return current -> value;
//         current = current -> next;
//     }
//     return NULL;
// }

void hashtable_print(HashTable* table) {
    for(size_t i = 0; i < BUCKETS; i++) {
        Node* current = table -> buckets[i] -> head;
        if(current != NULL) {
            printf("Bucket %i ", i);
            while(current != NULL) {
                printf("-> {%i:%p} ", current -> key, current -> value);
                current = current -> next;
            }
            printf("\n");
        }
    }
}