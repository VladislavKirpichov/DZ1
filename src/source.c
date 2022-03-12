#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "skyscraperio.h"

Skyscraper* input(FILE* file, size_t *size) {
    assert(file != NULL);

    Skyscraper* skyscrapers = NULL;
    skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors;
    int overallHeight;
    int spireHeight;
    char* purpose;
    char* region;

    size_t strSize = 0;
    char buf = '\0';
    while(!feof(file)) {

        fscanf(file, "%d", &numberOfFloors);
        fscanf(file, "%d", &overallHeight);
        fscanf(file, "%d", &spireHeight);

        // Check for valid data
        assert(numberOfFloors >= 0);
        assert(overallHeight >= 0);
        assert(spireHeight >= 0);

        // For purpose
        strSize = 2;
        purpose = calloc(strSize, sizeof(char));
        getc(file); buf = getc(file);
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0')) {
            purpose[strSize - 2] = buf;
            purpose[strSize - 1] = '\0';
            purpose = realloc(purpose, ++strSize);
            buf = getc(file);
        }

        assert(strlen(purpose) != 0);

        // For region
        strSize = 2;
        region = calloc(strSize, sizeof(char));
        buf = getc(file);
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0')) {
            region[strSize - 2] = buf;
            region[strSize - 1] = '\0';
            region = realloc(region, ++strSize);
            buf = getc(file);
        }

        assert(strlen(region) != 0);

        skyscrapers = realloc(skyscrapers, sizeof(Skyscraper) * (++*size));
        input_scyscraper(skyscrapers + *size - 1, numberOfFloors, overallHeight, spireHeight,
                         purpose, region);
    }
    
    fclose(file);
    return skyscrapers;
}

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
    FILE* file = fopen("../src/data.txt", "r");

    size_t size = 0;
    Skyscraper* skyscrapers = input(file, &size);

    group_by_purpose(skyscrapers, size);
    //sort_by_region(skyscrapers, 0, size - 1);

    output_scyscrapers_in_file(skyscrapers, size);
    free(skyscrapers);
    return 0;
}