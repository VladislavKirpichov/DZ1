//
// Created by Vladislav on 08.03.2022.
//

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "skyscraperio.h"

#define EXIT_CODE 1

//struct Skyscraper {
//    int numberOfFloors;
//    int overallHeight;
//    int spireHeight;
//
//    char* purpose;
//    char* region;
//};

Skyscraper* input(FILE* file, size_t *size) {
    if (file == NULL || ferror(file)) {
        fprintf(stderr, "File error!\n");
        return NULL;
    }

    Skyscraper* skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors = 0;
    int overallHeight = 0;
    int spireHeight = 0;
    char* purpose = NULL;
    char* region = NULL;

    size_t strSize = 0;
    char buf = '\0';
    while(!feof(file)) {

        if(fscanf(file, "%d", &numberOfFloors) == EOF) {
            return skyscrapers;
        };

        if(fscanf(file, "%d", &spireHeight) == EOF) {
            return skyscrapers;
        };

        if(fscanf(file, "%d", &overallHeight) == EOF) {
            return skyscrapers;
        };

        // Check for valid data
        if (numberOfFloors < 0) {
            fprintf(stderr, "numberOfFloors < 0\n");
            return NULL;
        }

        if (overallHeight < 0) {
            fprintf(stderr, "overallHeight < 0\n");
            return NULL;
        }

        if (spireHeight < 0) {
            fprintf(stderr, "spireHeight < 0\n");
            return NULL;
        }

        // For purpose
        strSize = 2;
        purpose = calloc(strSize, sizeof(char));
        purpose[1] = '\0';
        fgetc(file); buf = fgetc(file);
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0')) {
            purpose[strSize - 2] = buf;
            purpose[strSize - 1] = '\0';
            purpose = realloc(purpose, ++strSize);
            buf = getc(file);
        }

        if (strlen(purpose) == 0) {
            printf("%u", strSize);
            fprintf(stderr, "strlen(purpose) == 0, Size: %u", strSize);
            return NULL;
        }

        // For region
        strSize = 2;
        region = calloc(strSize, sizeof(char));
        region[1] = '\0';
        buf = fgetc(file);
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0')) {
            region[strSize - 2] = buf;
            region[strSize - 1] = '\0';
            region = realloc(region, ++strSize);
            buf = fgetc(file);
        }

        if (strlen(region) == 0) {
            if (buf == "\0") {
                return skyscrapers;
            }

            printf("%u", strSize);
            fprintf(stderr, "strlen(region) == 0, Size: %u", strSize);
            return NULL;
        }

        skyscrapers = realloc(skyscrapers, sizeof(Skyscraper) * (++*size));

        input_scyscraper(skyscrapers + *size - 1, numberOfFloors, overallHeight, spireHeight,
                         purpose, region);

        free(purpose);
        free(region);
    }

    return skyscrapers;
}

char input_scyscraper(Skyscraper *skyscraper, int numberOfFloors, int overallHeight, int spireHeight,
                            char* purpose, char* region) {
    
    if (skyscraper == NULL) {
        fprintf(stderr, "skyscraper == NULL\n");
        return 0;
    }

    if (purpose == NULL || *purpose == '\0') {
        fprintf(stderr, "purpose == NULL\n");
        return 0;
    }

    if (region == NULL || *region == '\0') {
        fprintf(stderr, "region == NULL\n");
        return 0;
    }

    skyscraper->numberOfFloors = numberOfFloors;
    skyscraper->overallHeight = overallHeight;
    skyscraper->spireHeight = spireHeight;

    skyscraper->purpose = malloc(strlen(purpose) + 1);

    // Check if we allocated memory
    if (skyscraper->purpose == NULL) {
        free(skyscraper->purpose);
        free(skyscraper);

        perror("malloc(skyscraper->purpose) returns == NULL");
        exit(EXIT_CODE);
    }

    skyscraper->region = malloc(strlen(region) + 1);

    // Check if we allocated memory
    if (skyscraper->region == NULL) {
        free(skyscraper->purpose);
        free(skyscraper->region);
        free(skyscraper);
        
        perror("malloc(skyscraper->region) returns NULL");
        return 0;
    }

    strcpy(skyscraper->purpose, purpose);
    strcpy(skyscraper->region, region);

    skyscraper->purpose[strlen(purpose)] = '\0';
    skyscraper->region[strlen(region)] = '\0';

    return 1;
}

void output_scyscrapers_in_file(const Skyscraper *const skyscrapers, size_t size) {
    FILE* file = fopen("./answer.txt", "w");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d %d %d %s %s\n", skyscrapers[i].numberOfFloors, skyscrapers[i].overallHeight,
               skyscrapers[i].spireHeight, skyscrapers[i].purpose, skyscrapers[i].region);
    }
    fclose(file);
}

// Copy second in first
char cpy(Skyscraper* first, Skyscraper* second) {
    if (first == NULL || second == NULL) {
        return 0;
    }

    first->numberOfFloors = second->numberOfFloors;
    first->overallHeight = second->overallHeight;
    first->spireHeight = second->spireHeight;

    free(first->purpose);
    free(first->region);

    first->purpose = malloc(strlen(second->purpose) + 1);
    if (first->purpose == NULL) {
        free(first->purpose);
        free(first);

        perror("malloc(first->purpose) returns NULL");
        exit(EXIT_CODE);
    }
    strcpy(first->purpose, second->purpose);
    // first->purpose[strlen(second->purpose)] = '\0';

    first->region = malloc(strlen(second->region) + 1);
    if (first->region == NULL) {
        free(first->purpose);
        free(first->region);
        free(first);

        perror("malloc(first->region) returns NULL");
        exit(EXIT_CODE);
    }
    strcpy(first->region, second->region);
    // first->region[strlen(second->region)] = '\0';

    return 1;
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

void swap(Skyscraper* first, Skyscraper* second) {
    Skyscraper* temp = malloc(sizeof(Skyscraper));
    temp->purpose = malloc(1);
    temp->region = malloc(1);
    
    cpy(temp, second);    // temp = second
    cpy(second, first);   // second = first
    cpy(first, temp);     // first = temp

    free(temp->purpose);
    free(temp->region);
    free(temp);
}

void free_skyscrapers(Skyscraper* skyscrapers, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        free((skyscrapers + i)->purpose);
        free((skyscrapers + i)->region);
    }

    free(skyscrapers);
}