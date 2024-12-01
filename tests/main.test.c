//
// Created by dan on 12/1/24.
//
#include <assert.h>
#include <stdio.h>

#include "../src/arrayList.h"
#include "../src/helpers.h"

void print_long_primitive(void *item) {
    long i = (long)item;
    printf("%ld", i);
}

void testArrayList() {
    array_list *list = al_create();
    const size_t initialCapacity = list->capacity;
    assert(list->size == 0);
    for (unsigned int i = 0; i < initialCapacity; i++) {
        al_push(list, NULL);
        assert(list->size == i + 1);
    }
    assert(list->size == initialCapacity);
    assert(list->capacity == initialCapacity);
    al_push(list, NULL);
    assert(list->capacity == (initialCapacity<<1));
    al_pop(list);
    assert(list->capacity == initialCapacity);
    assert(list->size == initialCapacity);
    al_destroy(list);
    printf("Array List Test finished with no assertion errors.\n");
}

void testArrayListProgram() {
    array_list *list = al_create();
    al_print(list, &print_long_primitive);
    al_push(list, (long *)5385);
    al_print(list, &print_long_primitive);
    al_push(list, (long *)434);
    al_print(list, &print_long_primitive);
    al_push(list, (long *)1);
    al_print(list, &print_long_primitive);
    al_push(list, (long *)69);
    al_print(list, &print_long_primitive);

    al_qsort(list, &cmp_long);
    al_print(list, &print_long_primitive);

    al_pop(list);
    al_print(list, &print_long_primitive);
    al_pop(list);
    al_print(list, &print_long_primitive);
    al_pop(list);
    al_print(list, &print_long_primitive);
    al_pop(list);
    al_print(list, &print_long_primitive);

    const size_t count = 100;

    for (int i = 0; i < count; ++i) {
        if (i < count / 2) al_push(list, (long *)i);
        else al_pop(list);
        printf("Size: %lu, Capacity: %lu - ", list->size, list->capacity);
        al_print(list, &print_long_primitive);
    }

    al_destroy(list);
}

int main(void) {
    testArrayList();
    testArrayListProgram();
    return 0;
}