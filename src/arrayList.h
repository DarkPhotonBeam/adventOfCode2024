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

typedef struct {
    size_t size;
    size_t capacity;
    void **data;
} array_list;

array_list *al_create();

void al_push(array_list *list, void *data);
void *al_pop(array_list *list);
void *al_get(const array_list *list, const size_t index);
void al_set(const array_list *list, const size_t index, void *data);
void al_destroy(array_list *list);
void al_print(const array_list *list, void (*print)(void *item));
void al_free(const array_list *list);
void al_qsort(const array_list *list, __compar_fn_t cmp_fn);

#endif //ARRAYLIST_H
