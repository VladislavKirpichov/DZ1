#include <stdio.h>
#include "skyscraperio.h"

int main() {
    size_t size = 0;
    FILE* file = fopen("../io/data.txt", "r");

    Skyscraper* skyscrapers;
    skyscrapers = input(file, &size);

    if (skyscrapers == NULL)
        return 0;

    group_by_purpose(skyscrapers, size);

    output_scyscrapers_in_file(skyscrapers, size);
    free_skyscrapers(skyscrapers, size);
    return 0;
}