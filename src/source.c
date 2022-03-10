#include <stdio.h>
#include <string.h>
#include "skyscraperio.h"

#define MAX_SIZE 100

Skyscraper* input(FILE* file, size_t *size) {
    if (file == NULL)
        printf("Error in file reading!");

    Skyscraper* skyscrapers = NULL;
    skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors;
    int overallHeight;
    int spireHeight;
    char* purpose;
    char* region;

    size_t strSize = 0;
    char buf = '\0';
    while(fscanf_s(file, "%d", &numberOfFloors) != EOF) {
        fscanf_s(file, "%d", &overallHeight);
        fscanf_s(file, "%d", &spireHeight);

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

        skyscrapers = realloc(skyscrapers, sizeof(Skyscraper) * (++*size));
        input_scyscraper(skyscrapers + *size - 1, numberOfFloors, overallHeight, spireHeight,
                         purpose, region);
    }

    fclose(file);
    return skyscrapers;
}

char check(const char* ch1, const char* ch2) {
    while (*ch1 == *ch2) {
        if (ch1 == ch2 == '\0')
            return 0;

        ch1++;
        ch2++;
    }

    return 0;
}

int group_by_purpose(Skyscraper *skyscrapers, size_t start, size_t end) {
    for (size_t i = start; i <= end - 1; ++i) {
        for (size_t j = i + 1; j <= end; ++j) {
            if (!strcmp(skyscrapers[j].purpose, skyscrapers[i].purpose)) {
                i++;
                swap(skyscrapers + j, skyscrapers + i);
            }
        }
    }
    return 0;
}

int group_by_region(Skyscraper *skyscrapers, size_t size) {
    int start = 0;
    int end = size;
    for (size_t i = 0; i < size - 1; ++i) {
        start = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (!strcmp(skyscrapers[j].region, skyscrapers[i].region)) {
                i++;
                swap(skyscrapers + j, skyscrapers + i);
            }
        }
        end = i;

        if (start != end) {
            group_by_purpose(skyscrapers, start, end);
        }
    }
    return 0;
}

int main() {
    FILE* file = fopen("../src/data.txt", "r");

    size_t size = 0;
    Skyscraper* skyscrapers = input(file, &size);

    group_by_region(skyscrapers, size);
    //sort_by_region(skyscrapers, 0, size - 1);

    output_scyscrapers_in_file(skyscrapers, size);
    free(skyscrapers);
    return 0;
}