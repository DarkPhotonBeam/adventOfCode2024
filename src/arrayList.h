//
// Created by dan on 12/1/24.
//

#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <stddef.h>
#include <stdlib.h>

#define ARRAY_LIST_INITIAL_CAPACITY 16

// TODO: Unit Tests

typedef struct {
    size_t size;
    size_t capacity;
    void **data;
} array_list;

inline array_list *al_create() {
    array_list *list = malloc(sizeof(array_list));
    list->size = 0;
    list->capacity = ARRAY_LIST_INITIAL_CAPACITY;
    list->data = malloc( ARRAY_LIST_INITIAL_CAPACITY * sizeof(void *) );
    return list;
}

inline void al_push(array_list *list, void *data) {
    if (list->size >= list->capacity) {
        list->capacity = list->capacity << 1;
        list->data = (void **)realloc(list->data, list->capacity * sizeof(void *));
    }
    list->data[list->size++] = data;
}

inline void *pop(array_list *list) {
    if (list->size == 0) return NULL;
    void *obj = list->data[--(list->size)];
    if (list->size <= (list->capacity >> 1)) {
        list->capacity >>= 1;
        list->data = (void **)realloc(list->data, list->capacity * sizeof(void *));
    }
    return obj;
}

inline void *al_get(const array_list *list, const size_t index) {
    return list->data[index];
}

inline void al_destroy(array_list *list) {
    free(list->data);
    free(list);
}

#endif //ARRAYLIST_H
