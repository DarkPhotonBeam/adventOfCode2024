//
// Created by dan on 12/1/24.
//

#include <stdio.h>
#include <stdlib.h>
#include "day1.h"
#include "../helpers.h"

#define ARR_INITIAL_SIZE 8

void day1(char *input) {
    FILE *f = NULL;

    if ( ( f = fopen(input, "r") ) == NULL ) {
        fprintf(stderr, "Could not open file %s\n", input);
        exit(1);
    }

    size_t capacity = ARR_INITIAL_SIZE;
    unsigned int *arrLeft = malloc( ARR_INITIAL_SIZE * sizeof(int) );
    unsigned int *arrRight = malloc( ARR_INITIAL_SIZE * sizeof(int) );

    size_t index = 0;

    while ( fscanf(f, "%u   %u", &arrLeft[index], &arrRight[index] ) != EOF ) {
        if (index >= capacity) {
            capacity = capacity << 1;
            arrLeft = realloc(arrLeft, capacity * sizeof(int));
            arrRight = realloc(arrRight, capacity * sizeof(int));
        }

        ++index;
    }

    qsort(arrLeft, index, sizeof(int), &cmp_int);
    qsort(arrRight, index, sizeof(int), &cmp_int);

    unsigned int total = 0;

    for (int i = 0; i < index; ++i) {
        unsigned int diff = abs(arrLeft[i] - arrRight[i]);
        //printf("%5u, %5u -> %5u\n", arrLeft[i], arrRight[i], diff);
        total += diff;
    }

    printf("PART ONE\nTotal sum of differences: %u\n\n", total);

    int rMin, rMax;
    findMinMax(arrRight, index, &rMin, &rMax);
    size_t spaceNeeded = rMax - rMin + 1;

    unsigned int *counts = malloc( spaceNeeded * sizeof(int) );

    for (unsigned int i = 0; i < spaceNeeded; ++i) counts[i] = 0;

    for (unsigned int i = 0; i < index; ++i) {
        size_t mapIndex = arrRight[i] - rMin;
        counts[mapIndex] += 1;
    }

    unsigned int similarity = 0;

    for (unsigned int i = 0; i < index; ++i) {
        if (arrLeft[i] < rMin || arrLeft[i] > rMax) continue;
        similarity += arrLeft[i] * counts[arrLeft[i] - rMin];
    }

    printf("PART TWO\nSimilarity score: %u\n\n", similarity);

    free(counts);
    free(arrLeft);
    free(arrRight);
    arrLeft = NULL;
    arrRight = NULL;

    fclose(f);
}
