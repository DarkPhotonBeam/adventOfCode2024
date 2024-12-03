//
// Created by dan on 12/1/24.
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stddef.h>
#include <stdlib.h>

#define ARRAY_LIST_INITIAL_CAPACITY 16
#define ARRAY_LIST_MIN_CAPACITY 4

// TODO: Unit Tests

typedef union {
        char charVal;
        short shortVal;
        int intVal;
        float floatVal;
        double doubleVal;
        long longVal;
        void *ptr;
} al_data;

typedef enum {
        AL_PM_CHAR,
        AL_PM_SHORT,
        AL_PM_INT,
        AL_PM_FLOAT,
        AL_PM_DOUBLE,
        AL_PM_LONG,
        AL_PM_PTR,
        AL_PM_STRING,
} al_print_mode;

typedef struct {
        size_t size;
        size_t capacity;
        al_data *data;
} array_list;

array_list *al_create();

// Can be used with al_allocate after this to have the array list struct on the stack instead of the heap
#define al_init() {.size = 0, .capacity = ARRAY_LIST_INITIAL_CAPACITY, .data = NULL}

void al_allocate(array_list *list);

void al_push(array_list *list, al_data data);

void al_pushChar(array_list *list, char data);

void al_pushLong(array_list *list, long data);

void al_pushInt(array_list *list, int data);

void al_pushPtr(array_list *list, void *data);

al_data al_pop(array_list *list);

al_data al_get(const array_list *list, const size_t index);

void al_set(const array_list *list, const size_t index, al_data data);

// Removes all array entries, sets size to 0
void al_clear(array_list *list);

void al_freeArray(const array_list *list);

void al_destroy(array_list *list);

void al_print(const array_list *list, al_print_mode print_mode);

void al_qsort(const array_list *list, __compar_fn_t cmp_fn);

#endif //ARRAYLIST_H
