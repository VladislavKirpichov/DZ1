//
// Created by Vladislav on 08.03.2022.
//

#ifndef DZ1_SKYSCRAPERIO_H
#define DZ1_SKYSCRAPERIO_H

#endif //DZ1_SKYSCRAPERIO_H

struct Skyscraper {
    int numberOfFloors;
    int overallHeight;
    int spireHeight;

    char* purpose;
    char* region;
};
typedef struct Skyscraper Skyscraper;

Skyscraper* input(FILE* file, size_t *size);

char input_scyscraper(Skyscraper *skyscraper, int numberOfFloors, int overallHeight, int spireHeight,
                            char* purpose, char* region);

void output_scyscrapers(const Skyscraper *const skyscraper, size_t size);
void output_scyscrapers_in_file(const Skyscraper *const skyscrapers, size_t size);

char cpy(Skyscraper* first, Skyscraper* second);
void swap(Skyscraper* first, Skyscraper* second);

int group_by_region(Skyscraper *skyscrapers, size_t start, size_t end);
int group_by_purpose(Skyscraper *skyscrapers, size_t size);

void free_skyscrapers(Skyscraper* skyscrapers, size_t size);