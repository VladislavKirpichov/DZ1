//
// Created by Vladislav on 08.03.2022.
//

#include <stdio.h>
#include <string.h>
#include "skyscraperio.h"

#define MAX_SIZE 100

//struct Skyscraper {
//    int numberOfFloors;
//    int overallHeight;
//    int spireHeight;
//
//    char* purpose;
//    char* region;
//};

char input_scyscraper_info(Skyscraper *skyscraper) {
    printf("%s", "Number of floors:");
    scanf("%u", &skyscraper->numberOfFloors);

    printf("%s", "Overral height:");
    scanf("%u", &skyscraper->overallHeight);

    printf("%s", "Spire height:");
    scanf("%u", &skyscraper->spireHeight);

    printf("%s", "Purpose of building:");
    const char *purpose[MAX_SIZE];
    scanf("%s", purpose);
    skyscraper->purpose = malloc(strlen(purpose) + 1);

    // Check if we allocated memory
    if (skyscraper->purpose == NULL) {
        free(skyscraper->purpose);
        free(skyscraper);
        return 0;
    }

    printf("%s", "Region:");
    const char *region[MAX_SIZE];
    scanf("%s", region);
    skyscraper->region = malloc(strlen(region) + 1);

    // Check if we allocated memory
    if (skyscraper->region == NULL) {
        free(skyscraper->purpose);
        free(skyscraper->region);
        free(skyscraper);
        return 0;
    }

    strcpy(skyscraper->purpose, purpose);
    strcpy(skyscraper->region, region);

    skyscraper->purpose[strlen(purpose)] = '\0';
    skyscraper->region[strlen(region)] = '\0';

    return 1;
}

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
        return 0;
    }

    skyscraper->region = malloc(strlen(region) + 1);

    // Check if we allocated memory
    if (skyscraper->region == NULL) {
        free(skyscraper->purpose);
        free(skyscraper->region);
        free(skyscraper);
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

char equal(Skyscraper* first, Skyscraper* second) {
    first->numberOfFloors = second->numberOfFloors;
    first->overallHeight = second->overallHeight;
    first->spireHeight = second->spireHeight;

    first->purpose = malloc(strlen(second->purpose));
    strcpy(first->purpose, second->purpose);
    if (first->purpose == NULL) {
        free(first->purpose);
        free(first);
        return 0;
    }

    first->region = malloc(strlen(second->region));
    strcpy(first->region, second->region);
    if (first->region == NULL) {
        free(first->region);
        free(first);
        return 0;
    }

    return 1;
}

void swap(Skyscraper* first, Skyscraper* second) {
    Skyscraper* temp = malloc(sizeof(Skyscraper));
    equal(temp, second);        // temp = second
    equal(second, first);// second = first
    equal(first, temp);     // first = temp
}