//
// Created by dan on 12/1/24.
//

#include "helpers.h"

#include <limits.h>
#include <stddef.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int cmp_int_rev(const void *a, const void *b) {
    return -cmp_int(a, b);
}

int cmp_long(const void *a, const void *b) {
    return (int)(*(long *)a - *(long *)b);
}

int cmp_long_rev(const void *a, const void *b) {
    return -cmp_long(a, b);
}

int sgn_cmp(int a, int b) {
    return (a < 0 && b < 0) || (a >= 0 && b >= 0);
}

void findMinMax(int *arr, const size_t size, int *min, int *max) {
    int currMin = INT_MAX;
    int currMax = INT_MIN;
    for (unsigned int i = 0; i < size; ++i) {
        if (arr[i] < currMin) currMin = arr[i];
        if (arr[i] > currMax) currMax = arr[i];
    }
    *min = currMin;
    *max = currMax;
}