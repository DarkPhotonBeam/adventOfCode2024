//
// Created by darkp on 04/12/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day4.h"
#include "../arrayList.h"
#include "../text.h"

#define WORD_LEN 4
#define W_FWD "XMAS"
#define W_INV "SMAX"

char cAt(array_list *rows, size_t row, size_t col) {
    return text_get(al_get(rows, row).ptr, col);
}

size_t horMatch(array_list *rows, size_t width, size_t row, size_t col) {
    if (col + WORD_LEN > width) return 0;
    int fwd = cAt(rows, row, col) == 'X' && cAt(rows, row, col + 1) == 'M' && cAt(rows, row, col + 2) == 'A' && cAt(rows, row, col + 3) == 'S';
    int inv = cAt(rows, row, col) == 'S' && cAt(rows, row, col + 1) == 'A' && cAt(rows, row, col + 2) == 'M' && cAt(rows, row, col + 3) == 'X';
    return fwd || inv;
}

size_t verMatch(array_list *rows, size_t width, size_t row, size_t col) {
    if (row + WORD_LEN > rows->size) return 0;
    int fwd = cAt(rows, row, col) == 'X' && cAt(rows, row + 1, col) == 'M' && cAt(rows, row + 2, col) == 'A' && cAt(rows, row + 3, col) == 'S';
    int inv = cAt(rows, row, col) == 'S' && cAt(rows, row + 1, col) == 'A' && cAt(rows, row + 2, col) == 'M' && cAt(rows, row + 3, col) == 'X';
    return fwd || inv;
}

size_t diagMatch(array_list *rows, size_t width, size_t row, size_t col) {
    if (col + WORD_LEN > width || row + WORD_LEN > rows->size) return 0;
    int fwd = cAt(rows, row, col) == 'X' && cAt(rows, row + 1, col + 1) == 'M' && cAt(rows, row + 2, col + 2) == 'A' && cAt(rows, row + 3, col + 3) == 'S';
    int inv = cAt(rows, row, col) == 'S' && cAt(rows, row + 1, col + 1) == 'A' && cAt(rows, row + 2, col + 2) == 'M' && cAt(rows, row + 3, col + 3) == 'X';
    return fwd || inv;
}

size_t diagRMatch(array_list *rows, size_t width, size_t row, size_t col) {
    if (col - 3 < 0 || row + WORD_LEN > rows->size) return 0;
    int fwd = cAt(rows, row, col) == 'X' && cAt(rows, row + 1, col - 1) == 'M' && cAt(rows, row + 2, col - 2) == 'A' && cAt(rows, row + 3, col - 3) == 'S';
    int inv = cAt(rows, row, col) == 'S' && cAt(rows, row + 1, col - 1) == 'A' && cAt(rows, row + 2, col - 2) == 'M' && cAt(rows, row + 3, col - 3) == 'X';
    return fwd || inv;
}

size_t countMatches(array_list *rows, size_t width, size_t row, size_t col) {
    return horMatch(rows, width, row, col) + verMatch(rows, width, row, col) + diagMatch(rows, width, row, col) + diagRMatch(rows, width, row, col);
}

int hasXMAS(array_list *rows, size_t width, size_t row, size_t col) {
    if (col == 0 || col == width-1 || row == 0 || row == rows->size-1 || cAt(rows, row, col) != 'A') return 0;
    int diag1 = (cAt(rows, row-1, col-1) == 'M' && cAt(rows, row+1, col+1) == 'S') || (cAt(rows, row-1, col-1) == 'S' && cAt(rows, row+1, col+1) == 'M');
    int diag2 = (cAt(rows, row+1, col-1) == 'M' && cAt(rows, row-1, col+1) == 'S') || (cAt(rows, row+1, col-1) == 'S' && cAt(rows, row-1, col+1) == 'M');
    return diag1 || diag2;
}

void day4(char *input) {
    FILE *f = NULL;

    if ((f = fopen(input, "r")) == NULL) {
        fprintf(stderr, "Could not open file %s\n", input);
        exit(1);
    }

    array_list *rows = al_create();

    al_pushPtr(rows, text_create());

    int c;
    while ( (c = getc(f)) != EOF ) {
        if (c != '\n') {
            text_pushc(al_get(rows, rows->size - 1).ptr, (char) c);
        } else {
            al_pushPtr(rows, text_create());
        }
    }

    size_t width = ((text_t *)al_get(rows, 0).ptr)->length;
    size_t total = 0;
    size_t x_mas_total = 0;

    for (size_t row = 0; row < rows->size; ++row) {
        for (size_t col = 0; col < width; ++col) {
            total += countMatches(rows, width, row, col);
            x_mas_total += hasXMAS(rows, width, row, col);
        }
    }

    printf("PART ONE\nTotal: %lu\n\n", total);
    printf("PART TWO\nTotal: %lu\n\n", x_mas_total);

    al_freeEntries(rows);
    al_destroy(rows);

    fclose(f);
}
