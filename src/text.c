//
// Created by dan on 12/3/24.
//

#include "text.h"

#include <stdio.h>

#include "helpers.h"

#include <stdlib.h>
#include <string.h>

text_t *text_create() {
        text_t *text = malloc(sizeof(text_t));

        text->length = 0;
        text->__capacity = TEXT_INITIAL_CAPACITY;
        text->str = malloc(TEXT_INITIAL_CAPACITY * sizeof(char));

        return text;
}

void text_pushc(text_t *text, char c) {
        if (text->length >= text->__capacity - 1) {
                text->__capacity <<= 1;
                text->str = realloc(text->str, text->__capacity * sizeof(char));
        }
        text->str[text->length++] = c;
        text->str[text->length] = '\0';
}

char text_get(text_t *text, size_t index) {
    return text->str[index];
}

void text_append(text_t *text, const char *str, const size_t n) {
        const size_t strLen = n;
        if (text->length + strLen > text->__capacity - 1) {
                size_t newCap = MAX(text->length + strLen, text->__capacity << 1);
                text->__capacity = newCap;
                text->str = realloc(text->str, newCap * sizeof(char));
                text->str[text->__capacity-1] = 0;
        }
        strncpy(text->str + text->length, str, n);
        text->length += n;
        text->str[text->length] = '\0';
}

void text_print(const text_t *text) {
        printf("%s\n", text->str);
}

void text_clear(text_t *text) {
        text->length = 0;
        text->__capacity = TEXT_INITIAL_CAPACITY;
        text->str = realloc(text->str, text->__capacity * sizeof(char));
}

void text_writeToStream(const text_t *text, FILE *stream) {
        fprintf(stream, "%s", text->str);
}

void text_writeToFile(const text_t *text, const char *path) {
        FILE *f;
        if ( (f = fopen(path, "w")) == NULL ) {
                fprintf(stderr, "Could not open file %s\n", path);
                return;
        }
        text_writeToStream(text, f);
        fclose(f);
}

long text_toLong(text_t *text) {
        char *endptr;
        const long result = strtol(text->str, &endptr, 10);
        if (endptr == text->str) {
                printf("rip bozo\n");
                exit(EXIT_FAILURE);
        }
        return result;
}

int text_toInt(text_t *text) {
        return (int) text_toLong(text);
}

void text_destroy(text_t *text) {
        free(text->str);
        text->str = NULL;
        free(text);
}