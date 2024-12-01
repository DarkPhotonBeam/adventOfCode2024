//
// Created by dan on 12/1/24.
//
#include <assert.h>

#include "../src/arrayList.h"

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
}

int main(void) {
    testArrayList();
    return 0;
}