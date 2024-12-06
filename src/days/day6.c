//
// Created by darkp on 06/12/2024.
//

#include "day6.h"
#include "../arrayList.h"
#include "../text.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UP '^'
#define RIGHT '>'
#define DOWN 'v'
#define LEFT '<'
#define MARKED 'X'
#define OBSTACLE '#'

int get_front(char dir, size_t width, size_t height, size_t currRow, size_t currCol, size_t *newRow, size_t *newCol) {
    *newRow = currRow;
    *newCol = currCol;
    if (dir == UP) {
        if (currRow == 0) return 0;
        --(*newRow);
    } else if (dir == RIGHT) {
        if (currCol == width - 1) return 0;
        ++(*newCol);
    } else if (dir == DOWN) {
        if (currRow == height - 1) return 0;
        ++(*newRow);
    } else if (dir == LEFT) {
        if (currCol == 0) return 0;
        --(*newCol);
    } else {
        return 0;
    }
    return 1;
}

char rotate_right(char currChar) {
    if (currChar == UP) return RIGHT;
    else if (currChar == RIGHT) return DOWN;
    else if (currChar == DOWN) return LEFT;
    else if (currChar == LEFT) return UP;
    else return currChar;
}

size_t walk(array_list *rowsTemplate, size_t initRow, size_t initCol) {
    array_list *rows = al_create();
    al_copyFrom(rows, rowsTemplate);
    char currDir = text_get(al_get(rowsTemplate, initRow).ptr, initCol);
    for (size_t i = 0; i < rows->size; ++i) {
        al_data d;
        d.ptr = text_createCopy(al_get(rowsTemplate, i).ptr);
        if (i == initRow) {
            text_set(d.ptr, initCol, '.');
        }
        al_set(rows, i, d);
    }
    size_t currRow = initRow, currCol = initCol;
    size_t width = ((text_t *)al_get(rows, 0).ptr)->length;

    size_t numDistinctPos = 0;

    int justRotated = 0;

    size_t moves = 0;

    while (currRow >= 0 && currRow < rows->size && currCol >= 0 && currCol < width) {
        char sym = text_get(al_get(rows, currRow).ptr, currCol);
        assert(sym != OBSTACLE);
        size_t newRow, newCol;
        if (sym != UP && sym != DOWN && sym != LEFT && sym != RIGHT) {
            ++numDistinctPos;
        } else if (sym == currDir) {
            return 0; // loop Detected
        }
        text_set(al_get(rows, currRow).ptr, currCol, currDir);
        if (!get_front(currDir, width, rows->size, currRow, currCol, &newRow, &newCol)) {
            break;
        }
        char frontSym = text_get(al_get(rows, newRow).ptr, newCol);
        if (frontSym == OBSTACLE) {
            currDir = rotate_right(currDir);
            if (sym == currDir) {
                return 0;
            }
            justRotated = 1;
            continue;
        }
        justRotated = 0;
        ++moves;
        if (moves > width * rows->size) return 0;
        currRow = newRow;
        currCol = newCol;
    }
    //for (size_t i = 0; i < rows->size; ++i) text_print(al_get(rows, i).ptr);
    al_freeEntries(rows);
    al_destroy(rows);
    return numDistinctPos;
}

void day6(char *input) {
    FILE *f;

    if ((f = fopen(input, "r")) == NULL) {
        fprintf(stderr, "Could not open file %s\n", input);
        exit(1);
    }

    array_list *rows = al_create();
    al_pushPtr(rows, text_create());

    size_t initRow, initCol;
    int ch;
    while ((ch = getc(f)) != EOF) {
        if (ch == '\n') {
            al_pushPtr(rows, text_create());
            continue;
        }
        text_t *curr = al_get(rows, rows->size-1).ptr;
        if (ch == UP || ch == RIGHT || ch == DOWN || ch == LEFT) {
            initRow = rows->size-1;
            initCol = curr->length;
        }
        text_pushc(curr, (char)ch);
    }
    if (((text_t *)al_get(rows, rows->size-1).ptr)->length == 0) al_pop(rows);

    size_t numDistinctPos = walk(rows, initRow, initCol);

    printf("PART ONE\nNumber of distinct positions: %lu\n\n", numDistinctPos);

    size_t numLoops = 0;

    for (size_t row = 0; row < rows->size; ++row) {
        text_t *text = al_get(rows, row).ptr;
        for (size_t col = 0; col < text->length; ++col) {
            printf("placing additional obstacle at (%lu, %lu)...\n", row, col);
            char sym = text_get(text, col);
            if (sym != '.') continue;
            text_set(al_get(rows, row).ptr, col, '#');
            size_t res = walk(rows, initRow, initCol);
            if (!res) {
                // Loop Detected!
                ++numLoops;
            }
            text_set(al_get(rows, row).ptr, col, '.');
        }
    }

    printf("PART TWO\nNum loops: %lu\n\n", numLoops);

    al_freeEntries(rows);
    al_destroy(rows);

    fclose(f);
}