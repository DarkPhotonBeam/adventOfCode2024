//
// Created by dan on 12/1/24.
// Doubly Linked List
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>

typedef union {
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
    INT,
    DOUBLE,
    LONG,
    PTR,
} ll_print_mode;

linked_list *ll_create();
void ll_add(linked_list *list, ll_data data);
void ll_insert(linked_list *list, ll_data data, size_t index);
void ll_addInt(linked_list *list, int data);
void ll_addDouble(linked_list *list, double data);
void ll_addLong(linked_list *list, long data);
void ll_addPtr(linked_list *list, void *data);
ll_data ll_delete(linked_list *list, size_t index);
ll_node *ll_get(linked_list *list, size_t index);
ll_data ll_getData(linked_list *list, size_t index);
ll_data ll_removeFirst(linked_list *list);
int ll_isEmpty(const linked_list *list);
void ll_destroy(linked_list *list);
void ll_print(const linked_list *list, ll_print_mode print_mode);


#endif //LINKEDLIST_H
