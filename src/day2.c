//
// Created by dan on 12/2/24.
//

#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

#include "arrayList.h"
#include "helpers.h"
#include "linkedList.h"

int isSafeReport(const array_list *report) {
    if (report->size <= 1) return 1;
    const int dir = al_get(report, 1).intVal - al_get(report, 0).intVal;
    for (int i = 0; i < report->size-1; ++i) {
        const int diff = al_get(report, i+1).intVal - al_get(report, i).intVal;
        if (!sgn_cmp(dir, diff) || abs(diff) > 3 || abs(diff) < 1) {
            return 0;
        }
    }
    return 1;
}

int isSafeReportWPD(const array_list *report) {
    if (report->size <= 2) return 1;

    int isSafe = 0;

    for (size_t i = 0; i < report->size; ++i) {
        array_list reportBar = al_init();
        al_allocate(&reportBar);

        for (size_t j = 0; j < report->size; ++j) {
            if (j == i) continue;
            al_pushInt(&reportBar, al_get(report, j).intVal);
        }

        if (isSafeReport(&reportBar)) {
            isSafe = 1;
        }

        al_freeArray(&reportBar);
        if (isSafe) return 1;
    }

    return 0;
}

void day2(char *input) {
    FILE *f = NULL;

    if ( ( f = fopen(input, "r") ) == NULL ) {
        fprintf(stderr, "Could not open file %s\n", input);
        exit(1);
    }

    array_list reports = al_init();
    al_allocate(&reports);

    al_pushPtr(&reports, al_create());

    size_t currReport = 0;
    int currInt;

    while ( ( fscanf(f, "%d", &currInt) ) != EOF ) {
        int sep = getc(f);
        al_pushInt(al_get(&reports, currReport).ptr, currInt);
        if (sep == '\n') {
            ++currReport;
            al_pushPtr(&reports, al_create());
        }
    }
    al_destroy(al_pop(&reports).ptr);

    size_t validCnt = 0;
    size_t safeCntWithPD = 0;

    for (size_t reportIndex = 0; reportIndex < reports.size; ++reportIndex) {
        array_list *report = al_get(&reports, reportIndex).ptr;

        if (isSafeReport(report)) ++validCnt;
        if (isSafeReportWPD(report)) ++safeCntWithPD;
    }

    printf("PART ONE\nNumber of safe reports: %lu\n\n", validCnt);
    printf("PART TWO\nNumber of safe reports with problem dampener: %lu\n\n", safeCntWithPD);

    for (int i = 0; i < reports.size; ++i) {
        //al_print(al_get(&reports, i).ptr, AL_PM_INT);
        al_destroy(al_get(&reports, i).ptr);
    }
    al_freeArray(&reports);

    fclose(f);
}
