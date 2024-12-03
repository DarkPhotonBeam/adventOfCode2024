//
// Created by dan on 12/1/24.
// Doubly Linked List
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>

typedef union {
    char charVal;
    float floatVal;
    short shortVal;
    int intVal;
    double doubleVal;
    long longVal;
    void *ptr;
} ll_data;

struct __ll_node {
    ll_data data;
    struct __ll_node *next;
    struct __ll_node *prev;
};

typedef struct __ll_node ll_node;

typedef struct {
    size_t size;
    ll_node *head;
    ll_node *tail;
} linked_list;

typedef enum {
    LL_PM_CHAR,
    LL_PM_SHORT,
    LL_PM_INT,
    LL_PM_FLOAT,
    LL_PM_DOUBLE,
    LL_PM_LONG,
    LL_PM_PTR
} ll_print_mode;

// Allocates memory for a linked list on the heap and returns pointer to it
linked_list *ll_create();

// Initializes empty linked_list on the stack, do not forget to call ll_freeNodes when you don't need the list anymore
#define ll_init() {.size = 0, .head = NULL, .tail = NULL}

// Adds a new node with the provided data at the end/head of the linked list
void ll_add(linked_list *list, ll_data data);

// Inserts a new node with the provided data at the specified index
void ll_insert(linked_list *list, ll_data data, size_t index);

// Wrapper function for ll_add for ints
void ll_addInt(linked_list *list, int data);

// Wrapper function for ll_add for doubles
void ll_addChar(linked_list *list, char data);

// Wrapper function for ll_add for doubles
void ll_addFloat(linked_list *list, float data);

// Wrapper function for ll_add for doubles
void ll_addShort(linked_list *list, short data);

// Wrapper function for ll_add for doubles
void ll_addDouble(linked_list *list, double data);

// Wrapper function for ll_add for longs
void ll_addLong(linked_list *list, long data);

// Wrapper function for ll_add for ptrs
void ll_addPtr(linked_list *list, void *data);

// Deletes and frees node at index
ll_data ll_delete(linked_list *list, size_t index);

// Returns the data in the node at the specified index
ll_data ll_getData(linked_list *list, size_t index);

void ll_setData(linked_list *list, size_t index, ll_data data);

void ll_setInt(linked_list *list, size_t index, int data);

// Removes and frees the first/tail node of the linked list and returns data of removed node
ll_data ll_removeFirst(linked_list *list);

// Returns 1 if linked list is empty, 0 otherwise
int ll_isEmpty(const linked_list *list);

// Destructively frees all nodes (makes linked list unusable)
void ll_freeNodes(linked_list *list);

// Frees memory of linked list
void ll_destroy(linked_list *list);

// Prints the linked list. print_mode determines formatting of data (LL_PM_INT, LL_PM_DOUBLE, LL_PM_LONG, LL_PM_PTR)
void ll_print(const linked_list *list, ll_print_mode print_mode);

// Creates and allocates memory for an array corresponding to the linked list
ll_data *ll_array(const linked_list *list);

void ll_setFromArray(linked_list *list, ll_data *arr, size_t size);

#endif //LINKEDLIST_H
