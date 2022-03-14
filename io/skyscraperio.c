//
// Created by Vladislav on 08.03.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "skyscraperio.h"

//struct Skyscraper {
//    int numberOfFloors;
//    int overallHeight;
//    int spireHeight;
//
//    char* purpose;
//    char* region;
//};

Skyscraper* input(FILE* file, size_t *size) {
    if (file == NULL)
        return NULL;

    Skyscraper* skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors = 0;
    int overallHeight = 0;
    int spireHeight = 0;
    char* purpose = NULL;
    char* region = NULL;

    size_t strSize = 0;
    char buf = '\0';
    while(!feof(file)) {

        fscanf(file, "%d", &numberOfFloors);
        fscanf(file, "%d", &overallHeight);
        fscanf(file, "%d", &spireHeight);

        // Check for valid data
        if (numberOfFloors <= 0) 
            return NULL;

        if (overallHeight <= 0) 
            return NULL;

        if (spireHeight < 0) 
            return NULL;

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

        if (strlen(purpose) == 0)
            return NULL;

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

        if (strlen(region) == 0)
            return NULL;

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
        return 0;
    }

    skyscraper->numberOfFloors = numberOfFloors;
    skyscraper->overallHeight = overallHeight;
    skyscraper->spireHeight = spireHeight;

    if (purpose == NULL || *purpose == '\0') {
        return 0;
    }

    skyscraper->purpose = malloc(strlen(purpose) + 1);

    // Check if we allocated memory
    if (skyscraper->purpose == NULL) {
        free(skyscraper->purpose);
        free(skyscraper);
        assert(skyscraper->purpose == NULL);
        return 0;
    }

    if (region == NULL || *region == '\0') {
        return 0;
    }

    skyscraper->region = malloc(strlen(region) + 1);

    // Check if we allocated memory
    if (skyscraper->region == NULL) {
        free(skyscraper->purpose);
        free(skyscraper->region);
        free(skyscraper);
        assert(skyscraper->region == NULL);
        return 0;
    }

    strcpy(skyscraper->purpose, purpose);
    strcpy(skyscraper->region, region);

    skyscraper->purpose[strlen(purpose)] = '\0';
    skyscraper->region[strlen(region)] = '\0';

    return 1;
}

void output_scyscrapers_in_file(const Skyscraper *const skyscrapers, size_t size) {
    FILE* file = fopen("../io/answer.txt", "w");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d\t%d\t%d\t%s\t%s\n", skyscrapers[i].numberOfFloors, skyscrapers[i].overallHeight,
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
        assert(first->purpose == NULL);
        return 0;
    }
    strcpy(first->purpose, second->purpose);
    // first->purpose[strlen(second->purpose)] = '\0';

    first->region = malloc(strlen(second->region) + 1);
    if (first->region == NULL) {
        free(first->purpose);
        free(first->region);
        free(first);
        assert(first->region == NULL);
        return 0;
    }
    strcpy(first->region, second->region);
    // first->region[strlen(second->region)] = '\0';

    return 1;
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