//
// Created by dan on 12/1/24.
//

#include "linkedList.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ll_node *ll_get(linked_list *list, size_t index);

linked_list *ll_create() {
    linked_list *list = malloc(sizeof(linked_list));
    if (list == NULL) {
        fprintf(stderr, "Failed to allocate memory for linked_list\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void ll_add(linked_list *list, ll_data data) {
    ll_node *node = malloc(sizeof(ll_node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->head->next = node;
        node->prev = list->head;
        list->head = node;
    }
    ++list->size;
}

void ll_insert(linked_list *list, ll_data data, size_t index) {
    assert(index <= list->size);
    if (index == list->size) {
        ll_add(list, data);
        return;
    }
    ll_node *node = malloc(sizeof(ll_node));
    node->data = data;

    if (index == 0) {
        node->next = list->tail;
        node->prev = NULL;
        list->tail->prev = node;
        list->tail = node;
    } else {
        ll_node *curr = ll_get(list, index);
        node->next = curr;
        node->prev = curr->prev;
        curr->prev->next = node;
        curr->prev = node;
    }

    ++list->size;
}

void ll_addChar(linked_list *list, const char data) {
    ll_data d;
    d.charVal = data;
    ll_add(list, d);
}

void ll_addInt(linked_list *list, const int data) {
    ll_data d;
    d.intVal = data;
    ll_add(list, d);
}

void ll_addShort(linked_list *list, const short data) {
    ll_data d;
    d.shortVal = data;
    ll_add(list, d);
}

void ll_addFloat(linked_list *list, const float data) {
    ll_data d;
    d.floatVal = data;
    ll_add(list, d);
}

void ll_addDouble(linked_list *list, const double data) {
    ll_data d;
    d.doubleVal = data;
    ll_add(list, d);
}

void ll_addLong(linked_list *list, const long data) {
    ll_data d;
    d.longVal = data;
    ll_add(list, d);
}

void ll_addPtr(linked_list *list, void *data) {
    ll_data d;
    d.ptr = data;
    ll_add(list, d);
}

ll_node *ll_get(linked_list *list, const size_t index) {
    assert(index < list->size);
    if (index >= list->size) return NULL;
    if (index == 0) return list->tail;
    if (index == list->size - 1) return list->head;
    ll_node *curr = NULL;
    size_t currIndex = 0;
    if (index >= list->size / 2) { // FROM HEAD
        currIndex = list->size - 1;
        curr = list->head;
        while (currIndex != index) {
            curr = curr->prev;
            --currIndex;
        }
    } else { // FROM TAIL
        curr = list->tail;
        while (currIndex != index) {
            curr = curr->next;
            ++currIndex;
        }
    }
    return curr;
}

ll_data ll_getData(linked_list *list, const size_t index) {
    return ll_get(list, index)->data;
}

void ll_setData(linked_list *list, size_t index, ll_data data) {
    ll_node *node = ll_get(list, index);
    node->data = data;
}

void ll_setInt(linked_list *list, size_t index, int data) {
    ll_data d;
    d.intVal = data;
    ll_setData(list, index, d);
}

ll_data ll_delete(linked_list *list, size_t index) {
    ll_data d = {};
    if (list->size == 0) return d;
    ll_node *node = ll_get(list, index);
    d = node->data;
    if (list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
    } else if (index == 0) { // DELETE TAIL
        list->tail = node->next;
        list->tail->prev = NULL;
    } else if (index == list->size - 1) { // DELETE HEAD
        list->head = node->prev;
        list->head->next = NULL;
    } else { // DELETE ANY
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
    node = NULL;
    --list->size;
    return d;
}

ll_data ll_removeFirst(linked_list *list) {
    return ll_delete(list, 0);
}

int ll_isEmpty(const linked_list *list) {
    return list->size == 0;
}

void ll_freeNodes(linked_list *list) {
    ll_node *node = list->head;
    while (node != NULL) {
        ll_node *nextNode = node->prev;
        free(node);
        node = nextNode;
    }
}

void ll_destroy(linked_list *list) {
    if (list == NULL) return;
    ll_freeNodes(list);
    free(list);
    list = NULL;
}

void ll_print(const linked_list *list, const ll_print_mode print_mode) {
    if (list == NULL) return;
    ll_node *node = list->tail;
    printf("[");
    while (node != NULL) {
        switch (print_mode) {
            case LL_PM_SHORT:
                printf("%hd", node->data.shortVal);
                break;
            case LL_PM_INT:
                printf("%d", node->data.intVal);
                break;
            case LL_PM_CHAR:
                printf("%c", node->data.charVal);
                break;
            case LL_PM_FLOAT:
            case LL_PM_DOUBLE:
                printf("%f", node->data.doubleVal);
                break;
            case LL_PM_LONG:
                printf("%ld", node->data.longVal);
                break;
            case LL_PM_PTR:
                printf("%p", node->data.ptr);
                break;
            default:
                break;
        }
        node = node->next;
        if (node != NULL) printf(",");
    }
    printf("]\n");
}

ll_data *ll_array(const linked_list *list) {
    ll_data *arr = malloc( list->size * sizeof(ll_data) );
    ll_node *curr = list->tail;
    size_t i = 0;
    while (curr != NULL) {
        arr[i++] = curr->data;
        curr = curr->next;
    }
    return arr;
}

void ll_setFromArray(linked_list *list, ll_data *arr, size_t size) {
    long diff = (long)(list->size - size);
    if (diff > 0) {
        for (long i = 0; i < diff; ++i) {
            ll_delete(list, list->size-1);
        }
    }
    if (diff < 0) {
        for (long i = 0; i < -diff; ++i) {
            ll_add(list, arr[size+diff+i]);
        }
    }
    ll_node *curr = list->tail;
    for (long i = 0; i < (size < list->size+diff ? size : list->size+diff); ++i) {
        curr->data = arr[i];
        curr = curr->next;
    }
}