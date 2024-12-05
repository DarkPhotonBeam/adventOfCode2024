//
// Created by dan on 12/5/24.
//

#include "day5.h"
#include "../uthash.h"
#include "../text.h"
#include "../helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
        int id;
        UT_hash_handle hh;
} page;

typedef struct {
        int id;
        page *p;
        UT_hash_handle hh;
} page_row;

static page *set = NULL;
static page_row *rel = NULL; // Relation Matrix

page_row *get_page_row(const int id) {
        page_row *row;
        HASH_FIND_INT(rel, &id, row);
        if (row == NULL) {
                row = (page_row *) malloc(sizeof(page_row));
                row->id = id;
                row->p = NULL;
                HASH_ADD_INT(rel, id, row);
        }
        return row;
}

void set_add(const int id) {
        page *p;
        HASH_FIND_INT(set, &id, p);
        if (p != NULL) return;
        p = (page *)malloc(sizeof(page));
        p->id = id;
        HASH_ADD_INT(set, id, p);
}

void set_pair(const int a, const int b) {

        page_row *row = get_page_row(a);
        page *p;
        HASH_FIND_INT(row->p, &b, p);
        if (p == NULL) {
                p = (page *) malloc(sizeof(page));
        }
        p->id = b;
        HASH_ADD_INT(row->p, id, p);
}

int get_pair(const int a, const int b) {
        const page_row *row = get_page_row(a);
        page *p;
        HASH_FIND_INT(row->p, &b, p);
        return p != NULL;
}

int check_if_strict_porder() {
        for (page *row = set; row != NULL; row = row->hh.next) {
                for (page *col = set; col != NULL; col = col->hh.next) {
                        int a = row->id;
                        int b = col->id;
                        if (a == b && get_pair(a, b)) {
                                printf("not irreflexive\n");
                                return 0; // not irreflexive
                        }
                        if (a != b && get_pair(a, b) == get_pair(b, a)) {
                                printf("not assymetric\n");
                                return 0; // not asymmetric
                        }
                        for (page *cpage = set; cpage != NULL; cpage = cpage->hh.next) {
                                int c = cpage->id;
                                if (!get_pair(a, b) || !get_pair(b, c)) continue;
                                if (!get_pair(a, c)) {
                                        printf("not transitive\n");
                                        return 0; // not transitive
                                }
                        }
                }
        }
        return 1;
}

int cmp_page(const void *a, const void *b) {
        al_data ad = *(const al_data *) a;
        al_data bd = *(const al_data *) b;
        int p1 = get_pair(ad.intVal, bd.intVal);
        int p2 = get_pair(bd.intVal, ad.intVal);
        if (p1 == p2) return 0;
        if (p1) return -1;
        return 1;
}

void day5(char *input) {
        clock_t s0 = clock();

        FILE *f = NULL;

        if ((f = fopen(input, "r")) == NULL) {
                fprintf(stderr, "Could not open file %s\n", input);
                exit(1);
        }

        text_t *num = text_create();
        array_list *update = al_create();

        int phase = 0;
        int ch;
        int prevCh = 0;
        int a = -1, b = -1;
        int currValid = 1;
        long total = 0, total2 = 0;
        while ( (ch = getc(f)) != EOF ) {
                if (phase == 0) {
                        if (is_digit((char)ch)) {
                                text_pushc(num, (char)ch);
                        } else if (ch == '|') {
                                a = text_toInt(num);
                                //printf("%d | ", a);
                                text_clear(num);
                        } else if (ch == '\n') {
                                if (prevCh == '\n') {
                                        phase = 1;
                                } else {
                                        b = text_toInt(num);
                                        //printf("%d\n", b);
                                        set_pair(a, b);
                                        text_clear(num);
                                }
                        }
                } else {
                        if (is_digit((char)ch)) {
                                text_pushc(num, (char)ch);
                        } else if (ch == ',' || ch == '\n') {
                                int c = text_toInt(num);
                                al_pushInt(update, c);
                                if (update->size >= 2) {
                                        int u = al_get(update, update->size-2).intVal;
                                        int v = al_get(update, update->size-1).intVal;
                                        if (!get_pair(u, v) || get_pair(v, u)) {
                                                currValid = 0;
                                        }
                                }
                                text_clear(num);
                                if (ch == '\n') {
                                        const size_t m = update->size / 2;
                                        if (currValid) total += al_get(update, m).intVal;

                                        if (!currValid) {
                                                //al_print(update, AL_PM_INT);
                                                al_qsort(update, &cmp_page);
                                                total2 += al_get(update, m).intVal;
                                        }
                                        //al_print(update, AL_PM_INT);
                                        al_destroy(update);
                                        update = al_create();
                                        currValid = 1;
                                }
                        }
                }
                prevCh = ch;
        }

        printf("total: %ld\n\ntotal 2: %ld\n\n", total, total2);

        for (page_row *row = rel; row != NULL; row = row->hh.next) {
                page *curr, *tmp;
                HASH_ITER(hh, row->p, curr, tmp) {
                        HASH_DEL(row->p, curr);
                        free(curr);
                }
        }

        page_row *curr, *tmp;
        HASH_ITER(hh, rel, curr, tmp) {
                HASH_DEL(rel, curr);
                free(curr);
        }

        al_destroy(update);
        text_destroy(num);

        fclose(f);

        clock_t s1 = clock();
        float seconds = (float)(s1 - s0) / CLOCKS_PER_SEC;
        printf("day5 took %f ms\n", seconds * 1000);
}