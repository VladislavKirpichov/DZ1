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

char input_scyscraper(Skyscraper *skyscraper, int numberOfFloors, int overallHeight, int spireHeight,
                            char* purpose, char* region) {
    skyscraper->numberOfFloors = numberOfFloors;
    skyscraper->overallHeight = overallHeight;
    skyscraper->spireHeight = spireHeight;

    skyscraper->purpose = malloc(strlen(purpose) + 1);

    // Check if we allocated memory
    if (skyscraper->purpose == NULL) {
        free(skyscraper->purpose);
        free(skyscraper);
        assert(skyscraper->purpose == NULL);
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

void output_scyscrapers(const Skyscraper *const skyscrapers, size_t size) {

    for (int i = 0; i < size; ++i) {
        printf("%s %d\n", "Number of floors:", skyscrapers[i].numberOfFloors);
        printf("%s %d\n", "Overral height:", skyscrapers[i].overallHeight);
        printf("%s %d\n", "Spire height:", skyscrapers[i].spireHeight);
        printf("%s %s\n", "Purpose:", skyscrapers[i].purpose);
        printf("%s %s\n\n", "Region:", skyscrapers[i].region);
    }
}

void output_scyscrapers_in_file(const Skyscraper *const skyscrapers, size_t size) {
    for (int i = 0; i < size; ++i) {
        printf("%d\t%d\t%d\t%s\t%s\n", skyscrapers[i].numberOfFloors, skyscrapers[i].overallHeight,
               skyscrapers[i].spireHeight, skyscrapers[i].purpose, skyscrapers[i].region);
    }
}

// Copy second in first
char cpy(Skyscraper* first, Skyscraper* second) {
    first->numberOfFloors = second->numberOfFloors;
    first->overallHeight = second->overallHeight;
    first->spireHeight = second->spireHeight;

    free(first->purpose);
    free(first->region);

    first->purpose = malloc(strlen(second->purpose));
    strcpy(first->purpose, second->purpose);
    if (first->purpose == NULL) {
        free(first->purpose);
        free(first);
        assert(first->purpose == NULL);
        return 0;
    }

    first->region = malloc(strlen(second->region));
    strcpy(first->region, second->region);
    if (first->region == NULL) {
        free(first->purpose);
        free(first->region);
        free(first);
        assert(first->region == NULL);
        return 0;
    }

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