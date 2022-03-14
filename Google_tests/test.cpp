#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "skyscraperio.h"
}

// TEST(Input, Input_From_File) {
//     Skyscraper skyscraper;
//     skyscraper.numberOfFloors = 2;
//     skyscraper.overallHeight = 2;
//     skyscraper.spireHeight = 2

//     skyscraper.purpose = new char(4);
//     strcpy(purpose, "test");

//     FILE* file = fmemopen("2 2 2 test test\n");
//     size_t size = 0;
//     Skyscraper* skyscrapers = input(file, &size);
//     EXPECT 
// }

TEST(Inputs, Input_errors_NULL_str) {
    char str[] = "test";
    char test[] = "\0";
    Skyscraper* skyscraper = new Skyscraper();
    EXPECT_EQ(0, input_scyscraper(NULL, 2, 2, 2, str, str));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, NULL, NULL));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, str, NULL));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, NULL, str));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, str, test));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, test, str));
    delete skyscraper;
}

bool check_if_eq(Skyscraper* skyscraper1, Skyscraper* skyscraper2) {
    if (skyscraper1->numberOfFloors != skyscraper2->numberOfFloors or
        skyscraper1->overallHeight != skyscraper2->overallHeight or
        skyscraper1->spireHeight != skyscraper2->spireHeight) {
            return false;
        }

    if (strcmp(skyscraper1->purpose, skyscraper2->purpose)) return false;
    if (strcmp(skyscraper1->region, skyscraper2->region)) return false;

    return 1;
}

TEST(Inputs, Inputs_logic) {
    // ASSERT_EQ // Приведет к падению теста сразу
    // EXPECT_EQ // Продолжит тест, но потом уведомит что тест тут упал

    // // fmemopen "меням работу с строчкой на работу с файлом"
    Skyscraper* skyscraper1 = new Skyscraper();
    Skyscraper* skyscraper2 = new Skyscraper();
    Skyscraper* skyscraper3 = new Skyscraper();
    Skyscraper* skyscraper4 = new Skyscraper();

    char myStr1[] = "test";

    input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    input_scyscraper(skyscraper2, 2, 2, 2, myStr1, myStr1);
    input_scyscraper(skyscraper3, 3, 5, 3, myStr1, myStr1);
    input_scyscraper(skyscraper4, 2, 2, 2, myStr1, "test");

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(false, check_if_eq(skyscraper1, skyscraper3));
    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper4));

    delete skyscraper1, skyscraper2, skyscraper3, skyscraper4;
}

TEST(Inputs, Input_from_file) {
    Skyscraper* skyscraper1 = new Skyscraper();
    Skyscraper* skyscraper2 = new Skyscraper();
    Skyscraper* skyscraper3 = new Skyscraper();
    Skyscraper* skyscraper4 = new Skyscraper();

    char buffer[] = "163 828 100 Residential Europe";
    FILE* file = fmemopen(buffer, strlen(buffer), "r"); // Open string like file

    size_t size = 0;
    skyscraper1 = input(file, &size);

    char purpose[] = "Residential";
    char region[] = "Europe";
    input_scyscraper(skyscraper2, 163, 828, 100, purpose, region);

    EXPECT_EQ(1, check_if_eq(skyscraper1, skyscraper2));
    fclose(file);

    // Check for errors
    char temp1[] = "";

    file = fmemopen(temp1, strlen(temp1), "r");
    EXPECT_EQ(NULL, input(NULL, &size));
    EXPECT_EQ(NULL, input(file, &size));
    fclose(file);

    char temp2[] = "0 828 100 Residential Europe";
    file = fmemopen(temp2, strlen(temp2), "r");
    EXPECT_EQ(NULL, input(NULL, &size));

    fclose(file);
    delete skyscraper1, skyscraper2, skyscraper3, skyscraper4;
}

TEST(Cpy, cpy) {
    Skyscraper* skyscraper1 = new Skyscraper();
    Skyscraper* skyscraper2 = new Skyscraper();

    char myStr1[] = "test";

    input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    cpy(skyscraper2, skyscraper1);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(false, cpy(skyscraper2, NULL));
    EXPECT_EQ(false, cpy(NULL, skyscraper2));
    
    delete skyscraper1, skyscraper2;
}

// TEST(Logic, Logic_simple_test) {
//     FILE* test1 = fopen("tests/answer.txt", "r");
//     FILE* answer1 = fopen("tests/answer1.txt", "r");

//     Skyscraper* skyscrapers = input("tests/test1.txt", &size);
//     group_by_purpose(skyscrapers, size);
//     output_scyscrapers_in_file(skyscrapers, size);
//     free_skyscrapers(skyscrapers, size);
    
//     EXPECT(answer1, test1);
// }