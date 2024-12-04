//
// Created by dan on 12/1/24.
//

#ifndef HELPERS_H
#define HELPERS_H
#include <stddef.h>

#include "arrayList.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

int cmp_int(const void *a, const void *b);
int cmp_int_rev(const void *a, const void *b);
int cmp_long(const void *a, const void *b);
int cmp_long_rev(const void *a, const void *b);

// Puts all regex matches in text into an array list and returns pointer to said array list
array_list *get_matches(const char *regex, const char *text);

// Returns 1 if a and b have same sign, 0 otherwise
int sgn_cmp(int a, int b);

// Iterates through array and stores min and max values in provided variables
void findMinMax(int *arr, const size_t size, int *min, int *max);

// Macro for max{a,b}
#define MAX(a, b) (a > b ? a : b)

// Macro for min{a, b}
#define MIN(a, b) (a < b ? a : b)

#endif //HELPERS_H
