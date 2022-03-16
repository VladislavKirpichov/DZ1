#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "skyscraperio.h"

int main() {
    size_t size = 0;
    FILE* file = fopen("../io/data.txt", "r");

    Skyscraper* skyscrapers = input(file, &size);

    if (skyscrapers == NULL) {
        fprintf(stderr, "error in input\n");
        return 0;
    }

    group_by_purpose(skyscrapers, size);

    output_scyscrapers_in_file(skyscrapers, size);
    free_skyscrapers(skyscrapers, size);
    return 0;
}