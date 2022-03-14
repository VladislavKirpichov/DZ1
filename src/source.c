#include <string.h>
#include <assert.h>
#include "skyscraperio.h"

int group_by_region(Skyscraper *skyscrapers, size_t start, size_t end) {
    for (size_t i = start; i <= end - 1; ++i) {
        for (size_t j = i + 1; j <= end; ++j) {
            if (!strcmp(skyscrapers[j].region, skyscrapers[i].region)) {
                i++;
                swap(skyscrapers + j, skyscrapers + i);
            }
        }
    }
    return 0;
}

int group_by_purpose(Skyscraper *skyscrapers, size_t size) {
    int start = 0;
    int end = size;
    for (size_t i = 0; i < size - 1; ++i) {
        start = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (!strcmp(skyscrapers[j].purpose, skyscrapers[i].purpose)) {
                i++;
                swap(skyscrapers + j, skyscrapers + i);
            }
        }
        end = i;

        if (start != end) {
            group_by_region(skyscrapers, start, end);
        }
    }
    return 0;
}

int main() {
    size_t size = 0;
    Skyscraper* skyscrapers = input(&size);

    group_by_purpose(skyscrapers, size);

    output_scyscrapers_in_file(skyscrapers, size);
    free_skyscrapers(skyscrapers, size);
    return 0;
}