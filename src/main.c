#include <stdio.h>
#include <stdlib.h>
#include "day1.h"

#define MAX_DAY 1

int getSelectedDay(int argc, char **argv) {
    int selectedDay = 1;

    if (argc > 1) {
        char *res;
        selectedDay = (int) strtol(argv[1], &res, 10);
        if ( argv[1] == res || selectedDay < 1 || selectedDay > MAX_DAY ) {
            fprintf(stderr, "Usage (1 <= day <= %d): ./adventOfCode2024 <day>\n", MAX_DAY);
            exit(1);
        }
    } else {
        printf("Please enter a day between 1 and %d: ", MAX_DAY);
        if ( scanf("%d", &selectedDay) != 1 ) {
            fprintf(stderr, "Invalid input.\n");
            exit(1);
        }
        if (selectedDay < 1 || selectedDay > MAX_DAY ) {
            fprintf(stderr, "Day must be between 1 and %d.\n", MAX_DAY);
            exit(1);
        }
    }

    printf("Selected day %d\n\n", selectedDay);

    return selectedDay;
}

void executeDay(int day) {
    if (day < 1 || day > MAX_DAY) return;
    switch (day) {
        case 1:
            day1("../inputs/day1.txt");
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    executeDay( getSelectedDay(argc, argv) );

    return 0;
}