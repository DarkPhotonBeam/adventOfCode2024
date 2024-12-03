//
// Created by dan on 12/3/24.
//

#include "day3.h"

#include <stdio.h>
#include <stdlib.h>

#include "../arrayList.h"

void day3(char *input) {
        FILE *f = NULL;

        if ((f = fopen(input, "r")) == NULL) {
                fprintf(stderr, "Could not open file %s\n", input);
                exit(1);
        }

        array_list buffer = al_init();
        al_allocate(&buffer);



        al_freeArray(&buffer);

        fclose(f);
}
