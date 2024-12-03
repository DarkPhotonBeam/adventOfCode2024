//
// Created by dan on 12/1/24.
//

#include "arrayList.h"

#include <stdio.h>

array_list *al_create() {
    array_list *list = malloc(sizeof(array_list));
    list->size = 0;
    list->capacity = ARRAY_LIST_INITIAL_CAPACITY;
    al_allocate(list);
    return list;
}

void al_allocate(array_list *list) {
    list->data = malloc(ARRAY_LIST_INITIAL_CAPACITY * sizeof(al_data));
}

void al_push(array_list *list, const al_data data) {
    if (list->size >= list->capacity) {
        list->capacity = list->capacity << 1;
        list->data = (al_data *) realloc(list->data, list->capacity * sizeof(al_data));
    }
    list->data[list->size++] = data;
}

void al_pushChar(array_list *list, const char data) {
    al_data d;
    d.charVal = data;
    al_push(list, d);
}

void al_pushLong(array_list *list, const long data) {
    al_data d;
    d.longVal = data;
    al_push(list, d);
}

void al_pushInt(array_list *list, const int data) {
    al_data d;
    d.intVal = data;
    al_push(list, d);
}

void al_pushPtr(array_list *list, void *data) {
    al_data d;
    d.ptr = data;
    al_push(list, d);
}

al_data al_pop(array_list *list) {
    const al_data nullData = {.longVal = 0};
    if (list->size == 0) return nullData;
    const al_data data = list->data[--(list->size)];
    if (list->size <= (list->capacity >> 1) && list->capacity > ARRAY_LIST_MIN_CAPACITY) {
        list->capacity >>= 1;
        list->data = (al_data *) realloc(list->data, list->capacity * sizeof(al_data));
    }
    return data;
}

al_data al_get(const array_list *list, const size_t index) {
    return list->data[index];
}

void al_set(const array_list *list, const size_t index, const al_data data) {
    list->data[index] = data;
}

void al_clear(array_list *list) {
    list->data = (al_data *) realloc( list->data, ARRAY_LIST_MIN_CAPACITY * sizeof(al_data) );
    list->size = 0;
    list->capacity = ARRAY_LIST_MIN_CAPACITY;
}

void al_freeArray(const array_list *list) {
    free(list->data);
}

void al_destroy(array_list *list) {
    al_freeArray(list);
    free(list);
}

void al_print(const array_list *list, al_print_mode print_mode) {
    printf("[");
    for (unsigned int i = 0; i < list->size; ++i) {
        const al_data data = list->data[i];
        switch (print_mode) {
            case AL_PM_INT:
                printf("%d", data.intVal);
                break;
            case AL_PM_FLOAT:
            case AL_PM_DOUBLE:
                printf("%f", data.floatVal);
                break;
            case AL_PM_CHAR:
                printf("%c", data.charVal);
                break;
            case AL_PM_PTR:
                printf("%p", data.ptr);
                break;
            case AL_PM_LONG:
                printf("%ld", data.longVal);
                break;
            case AL_PM_SHORT:
                printf("%hd", data.shortVal);
                break;
            case AL_PM_STRING:
                printf("%s", (char *) data.ptr);
                break;
        }
        if (i != (list->size - 1)) printf(", ");
    }
    printf("]\n");
}

void al_qsort(const array_list *list, const __compar_fn_t cmp_fn) {
    qsort(list->data, list->size, sizeof(void *), cmp_fn);
}
