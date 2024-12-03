//
// Created by dan on 12/1/24.
//

#ifndef HELPERS_H
#define HELPERS_H
#include <stddef.h>

int cmp_int(const void *a, const void *b);
int cmp_int_rev(const void *a, const void *b);
int cmp_long(const void *a, const void *b);
int cmp_long_rev(const void *a, const void *b);

int sgn_cmp(int a, int b);

void findMinMax(int *arr, const size_t size, int *min, int *max);

#define MAX(a, b) (a > b ? a : b)

#endif //HELPERS_H
