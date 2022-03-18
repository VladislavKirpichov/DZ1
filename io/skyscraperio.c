//
// Created by Vladislav on 08.03.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "skyscraperio.h"

Skyscraper* input(FILE* file, size_t *size) {
     if (file == NULL || ferror(file) || feof(file) || fgetc(file) == EOF) {
        fprintf(stderr, "File error!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    Skyscraper* skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors = 0;
    int overallHeight = 0;
    int spireHeight = 0;
    char* purpose;
    char* region = NULL;

    size_t strSize = 0;
    size_t tempSize = 0;
    char buf = '\0';
    while(fscanf(file, "%d", &numberOfFloors) != EOF &&
        fscanf(file, "%d", &overallHeight) != EOF &&
        fscanf(file, "%d", &spireHeight) != EOF) {

        fgetc(file);
        strSize = get_str(file, &purpose);

        if (strSize == -1) {
            fprintf(stderr, "get_str memory error (purpose)");
            return NULL;
        }

        else if (strSize == 0) {
            fprintf(stderr, "purpose size == 0");
            return NULL;
        }


        strSize = get_str(file, &region);

        if (strSize == -1) {
            fprintf(stderr, "get_str memory error (region)");
            return NULL;
        }

        else if (strSize == 0) {
            fprintf(stderr, "region size == 0");
            return NULL;
        }

        skyscrapers = realloc(skyscrapers, sizeof(Skyscraper) * (++*size));

        if (skyscrapers == NULL) {
            free(purpose);
            free(region);
            return NULL;
        }
        
        if (skyscraper_constructor(skyscrapers + *size - 1, numberOfFloors,
            overallHeight, spireHeight, purpose, region) == -1) {
            free(purpose);
            free(region);
            free(skyscrapers);
            return NULL;
        }

        free(purpose);
        free(region);
    }

    return skyscrapers;
}

// return -1: error in malloc 
int get_str(FILE* file, char** str) {
    size_t memSize;
    memSize = 1;

    size_t size;
    size = 2;

    char buf = '\0';

    memSize = 2;
    *str = malloc(sizeof(char)*memSize);

    if (*str == NULL)
        return -1;

    **str = '\0';
    buf = fgetc(file);

    while ((buf != EOF) && (buf != '\n') && (buf != ' ')
            && (buf != '\0') && (buf != '\t')) {

        *(*str + size - 2) = buf;
        *(*str + size - 1) = '\0';

        if (size == memSize) {
            memSize *= 2;
            *str = realloc(*str, memSize);

            if (*str == NULL) {
                return -1;
            }
        }
            
        size++;

        buf = fgetc(file);
    }

    return size;
}

int skyscraper_constructor(Skyscraper *skyscraper, int number_of_floors, int overall_height,
                      int spire_height, char* purpose, char* region) {
    
    if (skyscraper == NULL) {
        return 0;
    }

    skyscraper->numberOfFloors = number_of_floors;
    skyscraper->overallHeight = overall_height;
    skyscraper->spireHeight = spire_height;

    if (purpose == NULL || *purpose == '\0') {
        fprintf(stderr, "purpose == NULL || *purpose == '\0'");
        return 0;
    }
    
    skyscraper->purpose = malloc(strlen(purpose) + 1);

    // Check if we allocated memory
    if (skyscraper->purpose == NULL) {
        free(skyscraper->purpose);
        free(skyscraper);

        fprintf(stderr, "skyscraper->purpose == NULL");
        return -1;
    }

    if (region == NULL || *region == '\0') {
        free(skyscraper->purpose);
        fprintf(stderr, "region == NULL || *region == '\0'");
        return 0;
    }

    skyscraper->region = malloc(strlen(region) + 1);

    // Check if we allocated memory
    if (skyscraper->region == NULL) {
        free(skyscraper->purpose);
        free(skyscraper->region);
        free(skyscraper);

        fprintf(stderr, "skyscraper->region == NULL");
        return -1;
    }

    strcpy(skyscraper->purpose, purpose);
    strcpy(skyscraper->region, region);

    skyscraper->purpose[strlen(purpose)] = '\0';
    skyscraper->region[strlen(region)] = '\0';

    return 1;
}

void output_scyscrapers_in_file(const Skyscraper *const skyscrapers, size_t size) {
    FILE* file = fopen(ANSWER_FILE_NAME, "w");
    for (int i = 0; i < size; ++i) {
        fprintf(file, "%d %d %d %s %s\n", skyscrapers[i].numberOfFloors,
                skyscrapers[i].overallHeight, skyscrapers[i].spireHeight,
                skyscrapers[i].purpose, skyscrapers[i].region);
    }
    fclose(file);
}

int copy_skyscrapers(Skyscraper* dect, Skyscraper* src ) {
    if (dect == NULL || src == NULL) {
        return -1;
    }

    dect->numberOfFloors = src->numberOfFloors;
    dect->overallHeight = src->overallHeight;
    dect->spireHeight = src->spireHeight;

    dect->purpose = realloc(dect->purpose, strlen(src->purpose) + 1);
    if (dect->purpose == NULL) {
        free(dect->purpose);
        free(dect);
        
        fprintf(stderr, "dect->purpose = malloc return NULL");
        return 0;
    }

    if (dect->purpose != src->purpose) {
        strcpy(dect->purpose, src->purpose);
    }

    dect->purpose[strlen(src->purpose)] = '\0';

    dect->region = realloc(dect->region, strlen(src->region) + 1);

    if (dect->region == NULL) {
        free(dect->purpose);
        free(dect->region);
        free(dect);
        
        fprintf(stderr, "dect->dect = malloc return NULL");
        return 0;
    }
    
    if (dect->region != src->region) {
        strcpy(dect->region, src->region);
    }

    dect->region[strlen(src->region)] = '\0';

    return 1;
}

int group_by_region(Skyscraper *skyscrapers, size_t start, size_t end) {
    for (size_t i = start; i < end - 1; ++i) {
        for (size_t j = i + 1; j < end; ++j) {
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
        end = i + 1;

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
    
    copy_skyscrapers(temp, second);    // temp = second
    copy_skyscrapers(second, first);   // second = first
    copy_skyscrapers(first, temp);     // first = temp

    free(temp->purpose);
    free(temp->region);
    free(temp);
}

Skyscraper* free_skyscrapers(Skyscraper* skyscrapers, size_t size) {
    if (skyscrapers == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; ++i) {
        if ((skyscrapers + i)->purpose != NULL) {
            free((skyscrapers + i)->purpose);
        }
        
        if ((skyscrapers + i)->region != NULL) {
            free((skyscrapers + i)->region);
        }
    }

    free(skyscrapers);
    return skyscrapers;
}