//
// Created by dan on 12/3/24.
//

#include "day3.h"

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <time.h>

#include "../arrayList.h"
#include "../helpers.h"
#include "../text.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

typedef enum {
        DO,
        DONT,
        PREFIX,
        NUM1,
        NUM2,
        SUFFIX,
} parse_phase;

void day3_alt(char *input) {
        float totalTime = 0;
        clock_t s0 = clock();
        FILE *f = NULL;

        if ((f = fopen(input, "r")) == NULL) {
                fprintf(stderr, "Could not open file %s\n", input);
                exit(1);
        }

        text_t *text = text_create();

        // Read Input
        int c;
        while ( (c = getc(f)) != EOF ) {
                if (c == '\n') continue;
                text_pushc(text, c);
        }

        fclose(f);

        clock_t s1 = clock();

        float seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("READING TOOK %f ms\n", seconds * 1000);

        s0 = clock();

        array_list *matches = get_matches("mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)", text->str);

        s1 = clock();
        seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("REGEX TOOK %f ms\n", seconds * 1000);

        s0 = clock();

        int enabled = 1;
        long total = 0;
        long condTotal = 0;

        text_t *lNum = text_create(), *rNum = text_create();

        for (size_t i = 0; i < matches->size; ++i) {
                char *instr = al_get(matches, i).ptr;
                if (instr[2] == 'n') { // Don't
                        enabled = 0;
                } else if (instr[0] == 'd') { // Do
                        enabled = 1;
                } else { // Mul
                        size_t j = 4;
                        while ((c = instr[j++]) != ',') {
                                text_pushc(lNum, c);
                        }
                        while ((c = instr[j++]) != ')') {
                                text_pushc(rNum, c);
                        }
                        long a = text_toLong(lNum);
                        long b = text_toLong(rNum);
                        long prod = a * b;
                        total += prod;
                        if (enabled) condTotal += prod;
                        text_clear(lNum);
                        text_clear(rNum);
                }
        }

        text_destroy(lNum);
        text_destroy(rNum);
        lNum = NULL;
        rNum = NULL;

        al_freeEntries(matches);
        al_destroy(matches);

        printf("\n--> %ld, %ld <--\n\n", total, condTotal);

        s1 = clock();
        seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("PARSING TOOK %f ms\n", seconds * 1000);
        printf("DAY TOOK %f ms\n", totalTime * 1000);

        text_destroy(text);
}

void day3(char *input) {
        float totalTime = 0;
        clock_t s0 = clock();
        FILE *f = NULL;

        if ((f = fopen(input, "r")) == NULL) {
                fprintf(stderr, "Could not open file %s\n", input);
                exit(1);
        }

        text_t *text = text_create();
        text_t *sanitized_text = text_create();

        // Read Input
        int c;
        while ( (c = getc(f)) != EOF ) {
                if (c == '\n') continue;
                text_pushc(text, c);
        }

        fclose(f);

        clock_t s1 = clock();

        float seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("READING TOOK %f ms\n", seconds * 1000);

        s0 = clock();

        regex_t preg;
        regmatch_t pmatch[1];

        int regcompErr = regcomp(&preg, "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)", REG_EXTENDED);
        if (regcompErr) fprintf(stderr, "regcomp failed\n");

        char *s = text->str;

        for (unsigned int i = 0; ; i++) {
                if (regexec(&preg, s, ARRAY_SIZE(pmatch), pmatch, 0))
                        break;
                const regoff_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
                text_append(sanitized_text, s + pmatch[0].rm_so, len);
                text_pushc(sanitized_text, '\n');
                s += pmatch[0].rm_eo;
        }

        regfree(&preg);

        s1 = clock();
        seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("SANITIZING TOOK %f ms\n", seconds * 1000);
        s0 = clock();

        // Parse sanitized text
        long total = 0;
        long condTotal = 0;
        text_t *lNum = text_create(), *rNum = text_create();

        parse_phase phase = PREFIX;

        int enabled = 1;

        for (unsigned int i = 0; i < sanitized_text->length; ++i) {
                char ch = sanitized_text->str[i];
                switch (phase) {
                        case DO:
                                enabled = 1;
                                if (ch == ')') phase = PREFIX;
                                if (ch == 'n') phase = DONT;
                                break;
                        case DONT:
                                enabled = 0;
                                if (ch == ')') phase = PREFIX;
                                break;
                        case PREFIX:
                                if (ch == 'd') phase = DO;
                                if (ch == '(') phase = NUM1;
                                break;
                        case NUM1:
                                if (ch == ',') phase = NUM2;
                                else text_pushc(lNum, ch);
                                break;
                        case NUM2:
                                if (ch == ')') phase = SUFFIX;
                                else text_pushc(rNum, ch);
                                break;
                        case SUFFIX:
                                long mulRes = text_toLong(lNum) * text_toLong(rNum);
                                total += mulRes;
                                if (enabled) condTotal += mulRes;

                                text_clear(lNum);
                                text_clear(rNum);
                                phase = PREFIX;
                                break;
                }
        }

        s1 = clock();
        seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("PARSING TOOK %f ms\n", seconds * 1000);
        s0 = clock();

        printf("\nPART ONE\nTotal: %ld\n\n", total);
        printf("PART TWO\nConditional Total: %ld\n\n", condTotal);

        text_destroy(lNum);
        text_destroy(rNum);
        lNum = NULL;
        rNum = NULL;

        // Free heap-allocated memory
        text_destroy(text);
        text_destroy(sanitized_text);
        text = NULL;
        sanitized_text = NULL;
        s1 = clock();
        seconds = (float)(s1-s0) / CLOCKS_PER_SEC;
        totalTime += seconds;
        printf("CLEANUP TOOK %f ms\n", seconds * 1000);
        printf("DAY3 TIME %f ms\n", totalTime * 1000);
}
