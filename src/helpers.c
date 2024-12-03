//
// Created by dan on 12/1/24.
//

#include "helpers.h"

#include <limits.h>
#include <stddef.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

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

array_list *get_matches(const char *regex, const char *text) {
    const char *end = strlen(text) + text;

    regex_t preg;
    regmatch_t pmatch[1];

    if (regcomp(&preg, regex, REG_EXTENDED)) {
        fprintf(stderr, "Regex (%s) compilation failed.\n", regex);
        return NULL;
    }

    const char *strPtr = text;

    array_list *matches = al_create();

    while (!regexec(&preg, strPtr, ARRAY_SIZE(pmatch), pmatch, 0) && strPtr <= end) {
        regoff_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
        char *str = malloc((len + 1) * sizeof(char));
        for (size_t i = 0; i < len; ++i) {
            str[i] = *(strPtr + pmatch[0].rm_so + i);
        }
        str[len] = '\0';
        al_pushPtr(matches, str);
        strPtr += pmatch[0].rm_eo;
    }

    regfree(&preg);
    return matches;
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