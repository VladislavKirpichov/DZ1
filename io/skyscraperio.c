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
     if (file == NULL || ferror(file) || feof(file) || fgetc(file) == EOF) {
        fprintf(stderr, "File error!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_SET);

    Skyscraper* skyscrapers = malloc(sizeof(Skyscraper));

    int numberOfFloors = 0;
    int overallHeight = 0;
    int spireHeight = 0;
    char* purpose = NULL;
    char* region = NULL;

    size_t strSize = 0;
    size_t tempSize = 0;
    char buf = '\0';
    while(fscanf(file, "%d", &numberOfFloors) != EOF &&
        fscanf(file, "%d", &overallHeight) != EOF &&
        fscanf(file, "%d", &spireHeight) != EOF) {

        // For purpose
        strSize = 2;
        tempSize = 2;
        purpose = calloc(strSize, sizeof(char)*1);

        if (purpose == NULL) {
            fprintf(stderr, "purpose == NULL");
            return NULL;
        }
        
        purpose[0] = '\0';
        fgetc(file); buf = fgetc(file);
        // strpbrk
        // Мб написать, что тут динамически выделяется и поэтому не могу fscanf?
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0') && (buf != '\t')) {
            purpose[tempSize - 2] = buf;
            purpose[tempSize - 1] = '\0';

            if (tempSize == strSize - 1) {
                strSize *= 2;
                purpose = realloc(purpose, strSize);

                if (purpose == NULL) {
                    fprintf(stderr, "realloc(purpose) returns NULL");
                    return NULL;
                }
            }
            
            tempSize++;
            
            buf = fgetc(file);
        }

        printf("%c", *purpose);

        if (strlen(purpose) == 0) {
            fprintf(stderr, "%c", *purpose);
            return NULL;
        }

        // For region
        strSize = 2;
        tempSize = 2;
        region = calloc(strSize, sizeof(char));

        if (region == NULL) {
            fprintf(stderr, "region == NULL");
        }

        region[0] = '\0';
        buf = fgetc(file);
        while ((buf != EOF) && (buf != '\n') && (buf != ' ') && (buf != '\0') && (buf != '\t')) {
            region[tempSize - 2] = buf;
            region[tempSize - 1] = '\0';

            if (tempSize == strSize - 1) {
                strSize *= 2;
                region = realloc(region, strSize);

                if (region == NULL) {
                    fprintf(stderr, "realloc(purpose) returns NULL");
                    return NULL;
                }
            }
            
            tempSize++;

            buf = fgetc(file);
        }

        if (strlen(region) == 0) {
            fprintf(stderr, "strlen(region) == 0, Size: %u\n", strSize);
            return NULL;
        }

        skyscrapers = realloc(skyscrapers, sizeof(Skyscraper) * (++*size));

        if (skyscrapers == NULL) {
            free(purpose);
            free(region);
            return NULL;
        }
        
        if (!input_scyscraper(skyscrapers + *size - 1, numberOfFloors,
            overallHeight, spireHeight, purpose, region)) {
                free(purpose);
                free(region);
                return NULL;
        }

        free(purpose);
        free(region);
    }

    return skyscrapers;
}

int input_scyscraper(Skyscraper *skyscraper, int numberOfFloors, int overallHeight,
                      int spireHeight, char* purpose, char* region) {
    
    if (skyscraper == NULL) {
        return 0;
    }

    skyscraper->numberOfFloors = numberOfFloors;
    skyscraper->overallHeight = overallHeight;
    skyscraper->spireHeight = spireHeight;

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

        // Код ошибки продумать
        return 0;
    }

    dect->numberOfFloors = src->numberOfFloors;
    dect->overallHeight = src->overallHeight;
    dect->spireHeight = src->spireHeight;

    free(dect->purpose);
    free(dect->region);

    dect->purpose = malloc(strlen(src->purpose) + 1);
    if (dect->purpose == NULL) {
        free(dect->purpose);
        free(dect);
        
        fprintf(stderr, "dect->purpose = malloc return NULL");
        return 0;
    }
    strcpy(dect->purpose, src->purpose);
    dect->purpose[strlen(src->purpose)] = '\0';

    dect->region = malloc(strlen(src->region) + 1);
    if (dect->region == NULL) {
        free(dect->purpose);
        free(dect->region);
        free(dect);
        
        fprintf(stderr, "dect->dect = malloc return NULL");
        return 0;
    }
    strcpy(dect->region, src->region);
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
    for (size_t i = 0; i < size; ++i) {
        free((skyscrapers + i)->purpose);
        free((skyscrapers + i)->region);
    }

    free(skyscrapers);
    return skyscrapers;
}