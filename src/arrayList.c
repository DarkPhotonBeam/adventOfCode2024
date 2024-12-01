//
// Created by dan on 12/1/24.
//

#include "arrayList.h"

#include <stdio.h>

array_list *al_create() {
    array_list *list = malloc(sizeof(array_list));
    list->size = 0;
    list->capacity = ARRAY_LIST_INITIAL_CAPACITY;
    list->data = malloc( ARRAY_LIST_INITIAL_CAPACITY * sizeof(void *) );
    return list;
}

void al_push(array_list *list, void *data) {
    if (list->size >= list->capacity) {
        list->capacity = list->capacity << 1;
        list->data = (void **)realloc(list->data, list->capacity * sizeof(void *));
    }
    list->data[list->size++] = data;
}

void *al_pop(array_list *list) {
    if (list->size == 0) return NULL;
    void *obj = list->data[--(list->size)];
    if (list->size <= (list->capacity >> 1) && list->capacity > ARRAY_LIST_MIN_CAPACITY) {
        list->capacity >>= 1;
        list->data = (void **)realloc(list->data, list->capacity * sizeof(void *));
    }
    return obj;
}

void *al_get(const array_list *list, const size_t index) {
    return list->data[index];
}

void al_set(const array_list *list, const size_t index, void *data) {
    list->data[index] = data;
}

void al_destroy(array_list *list) {
    free(list->data);
    free(list);
}

void al_print(const array_list *list, void (*print)(void *item)) {
    printf("[");
    for (unsigned int i = 0; i < list->size; ++i) {
        print(list->data[i]);
        if (i != (list->size - 1)) printf(", ");
    }
    printf("]\n");
}

void al_free(const array_list *list) {
    for (unsigned int i = 0; i < list->size; ++i) {
        free(list->data[i]);
    }
}

void al_qsort(const array_list *list, const __compar_fn_t cmp_fn) {
    qsort(list->data, list->size, sizeof(void *), cmp_fn);
}