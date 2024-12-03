//
// Created by dan on 12/3/24.
//

#ifndef TEXT_H
#define TEXT_H
#include <stddef.h>

#define TEXT_INITIAL_CAPACITY 8

typedef struct {
        size_t length;
        size_t __capacity;
        char *str;
} text_t;

text_t *text_create();

void text_pushc(text_t *text, char c);

void text_append(text_t *text, const char *str, const size_t n);

void text_print(const text_t *text);

void text_clear(text_t *text);

long text_toLong(text_t *text);

int text_toInt(text_t *text);

void text_destroy(text_t *text);

#endif //TEXT_H
