//
// Created by dan on 12/1/24.
//
#include <assert.h>
#include <stdio.h>

#include "../src/arrayList.h"
#include "../src/linkedList.h"
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
        al_pushLong(list, 0);
        assert(list->size == i + 1);
    }
    assert(list->size == initialCapacity);
    assert(list->capacity == initialCapacity);
    al_pushLong(list, 0);
    assert(list->capacity == (initialCapacity<<1));
    al_pop(list);
    assert(list->capacity == initialCapacity);
    assert(list->size == initialCapacity);
    al_destroy(list);
    printf("Array List Test finished with no assertion errors.\n");
}

void testArrayListProgram() {
    array_list *list = al_create();
    al_print(list, AL_PM_LONG);
    al_pushLong(list, 24);
    al_print(list, AL_PM_LONG);
    al_pushLong(list, 434);
    al_print(list, AL_PM_LONG);
    al_pushLong(list, 1);
    al_print(list, AL_PM_LONG);
    al_pushLong(list, 42);
    al_print(list, AL_PM_LONG);

    al_qsort(list, &cmp_long);
    al_print(list, AL_PM_LONG);

    al_pop(list);
    al_print(list, AL_PM_LONG);
    al_pop(list);
    al_print(list, AL_PM_LONG);
    al_pop(list);
    al_print(list, AL_PM_LONG);
    al_pop(list);
    al_print(list, AL_PM_LONG);

    const size_t count = 100;

    for (int i = 0; i < count; ++i) {
        if (i < count / 2) al_pushLong(list, i);
        else al_pop(list);
        printf("Size: %lu, Capacity: %lu - ", list->size, list->capacity);
        al_print(list, AL_PM_LONG);
    }

    al_destroy(list);
}

void testLinkedList() {
    size_t sized = sizeof(al_data);
    printf("Size: %lu\n", sized);
    linked_list bruh = ll_init();
    ll_data arrInit[6] = {5, 420, 14, 49248, -424, 42};
    linked_list *list = &bruh;
    ll_setFromArray(list, arrInit, 6);
    ll_print(list, LL_PM_INT);
    ll_data d = ll_getData(list, 3);
    printf("%d\n", d.intVal);
    ll_data num = {.intVal = 10000};
    ll_insert(list, num, 3);
    ll_print(list, LL_PM_INT);

    ll_data *arr = ll_array(list);

    for (int i = 0; i < list->size; ++i) {
        printf("%d\n", arr[i].intVal);
    }

    ll_data iArr[7] = {1, 2, 3, 4, 5, 6, 7};
    ll_setFromArray(list, iArr, 7);
    free(arr);

    ll_print(list, LL_PM_INT);

    ll_delete(list, 3);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 3);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 3);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 3);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 0);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 0);
    ll_print(list, LL_PM_INT);
    ll_addInt(list, 666);
    ll_print(list, LL_PM_INT);
    ll_delete(list, 0);
    ll_print(list, LL_PM_INT);
    ll_freeNodes(list);
    //ll_destroy(list);
}

int main(void) {
    testArrayList();
    testArrayListProgram();
    testLinkedList();

    array_list list = al_init();
    al_allocate(&list);

    al_pushPtr(&list, "hello");
    al_pushPtr(&list, "world");
    al_pushPtr(&list, "it's");
    al_pushPtr(&list, "me");

    al_print(&list, AL_PM_STRING);

    al_freeArray(&list);

    return 0;
}