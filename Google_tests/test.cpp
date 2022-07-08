#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "skyscraperio.h"
}

bool check_if_eq(Skyscraper* skyscraper1, Skyscraper* skyscraper2) {
    if (skyscraper1->numberOfFloors != skyscraper2->numberOfFloors ||
        skyscraper1->overallHeight != skyscraper2->overallHeight ||
        skyscraper1->spireHeight != skyscraper2->spireHeight) {
            return false;
        }

    if (strcmp(skyscraper1->purpose, skyscraper2->purpose) &&
        strcmp(skyscraper1->region, skyscraper2->region)) return false;

    return true;
}

bool check_if_eq_files(FILE* file1, FILE* file2) {
    char ch1 = fgetc(file1);
    char ch2 = fgetc(file2);

    size_t size = 0;
    while (ch1 != EOF && ch2 != EOF) {
        ch1 = fgetc(file1);
        ch2 = fgetc(file2);

        if (ch1 != ch2) 
            return false;
    }

    if (ch1 == EOF && ch2 == EOF) return true;
    return false;
}

TEST(Inputs, Input_errors_NULL_str) {
    char str[] = "test";
    char test[] = "\0";
    Skyscraper* skyscraper = (Skyscraper*)malloc(sizeof(Skyscraper));
    EXPECT_EQ(0, skyscraper_constructor(NULL, 2, 2, 2, str, str));
    EXPECT_EQ(0, skyscraper_constructor(skyscraper, 2, 2, 2, NULL, NULL));
    EXPECT_EQ(0, skyscraper_constructor(skyscraper, 2, 2, 2, str, NULL));
    EXPECT_EQ(0, skyscraper_constructor(skyscraper, 2, 2, 2, NULL, str));
    EXPECT_EQ(0, skyscraper_constructor(skyscraper, 2, 2, 2, str, test));
    EXPECT_EQ(0, skyscraper_constructor(skyscraper, 2, 2, 2, test, str));
    free(skyscraper);
}

TEST(Constructor, Constructor_logic) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper3 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper4 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char myStr1[] = "test";

    skyscraper_constructor(skyscraper1, 2, 2, 2, myStr1, myStr1);
    skyscraper_constructor(skyscraper2, 2, 2, 2, myStr1, myStr1);
    skyscraper_constructor(skyscraper3, 3, 5, 3, myStr1, myStr1);
    skyscraper_constructor(skyscraper4, 2, 2, 2, myStr1, myStr1);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(false, check_if_eq(skyscraper1, skyscraper3));
    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper4));

    free_skyscrapers(skyscraper1, 1);
    free_skyscrapers(skyscraper2, 1);
    free_skyscrapers(skyscraper3, 1);
    free_skyscrapers(skyscraper4, 1);
}

TEST(Inputs, Input_from_file) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char buffer[] = "163 828 100 Residential Europe";
    FILE* file1 = fmemopen(buffer, strlen(buffer), "r");

    size_t size;
    size = 0;
    skyscraper1 = input(file1, &size);

    char purpose[] = "Residential";
    char region[] = "Europe";
    skyscraper_constructor(skyscraper2, 163, 828, 100, purpose, region);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    fclose(file1);
    free_skyscrapers(skyscraper1, size);
    free_skyscrapers(skyscraper2, 1);

    // Check for error
    EXPECT_EQ(NULL, input(NULL, &size));
}

TEST(Cpy, cpy_test) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char myStr1[] = "test";
    char myStr2[] = "new str for test";

    skyscraper_constructor(skyscraper1, 2, 2, 2, myStr1, myStr1);
    skyscraper_constructor(skyscraper2, 100, 100, 100, myStr1, myStr1);
    copy_skyscrapers(skyscraper2, skyscraper1);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(-1, copy_skyscrapers(skyscraper2, NULL));
    EXPECT_EQ(-1, copy_skyscrapers(NULL, skyscraper2));
    
    free_skyscrapers(skyscraper1, 1);
    free_skyscrapers(skyscraper2, 1);
}

TEST(Group, group_logic) {
    char inputStr[] = "163 828 100 Residential Europe\n163 828 100 Gym Europe\n163 828 100 Residential Europe\0";
    FILE* inputFile = fmemopen(inputStr, strlen(inputStr), "r"); // Open string like file

    char answerStr[] = "163 828 100 Residential Europe\n163 828 100 Residential Europe\n163 828 100 Gym Europe\0";
    FILE* answerFile = fmemopen(answerStr, strlen(answerStr), "r"); // Open string like file

    size_t inputSize = 0, answerSize = 0;
    Skyscraper* skyscraper1 = input(inputFile, &inputSize);
    Skyscraper* skyscraper2 = input(answerFile, &answerSize);

    group_by_purpose(skyscraper1, inputSize);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));

    free_skyscrapers(skyscraper1, inputSize);
    free_skyscrapers(skyscraper2, answerSize);

    fclose(inputFile);
    fclose(answerFile);
}

TEST(General, general_test1) {
    FILE* inputFile = fopen("./Google_tests/tests/test1.txt", "r");
    FILE* answerFile = fopen("./Google_tests/answers/answer1.txt", "r");
    size_t inputSize = 0;

    // Logic
    Skyscraper* skyscrapers = input(inputFile, &inputSize);
    group_by_purpose(skyscrapers, inputSize);
    output_scyscrapers_in_file(skyscrapers, inputSize);
    free_skyscrapers(skyscrapers, inputSize);

    // Program answer
    FILE* testAnswerFile = fopen("./answer.txt", "r");

    fseek(inputFile, SEEK_SET, SEEK_SET);
    EXPECT_EQ(true, check_if_eq_files(answerFile, testAnswerFile));
    fclose(inputFile);
    fclose(answerFile);
    fclose(testAnswerFile);
}

TEST(General, general_test2) {
    FILE* inputFile = fopen("./Google_tests/tests/test2.txt", "r");
    FILE* answerFile = fopen("./Google_tests/answers/answer2.txt", "r");
    size_t inputSize = 0;

    // Logic
    Skyscraper* skyscrapers = input(inputFile, &inputSize);
    group_by_purpose(skyscrapers, inputSize);
    output_scyscrapers_in_file(skyscrapers, inputSize);
    free_skyscrapers(skyscrapers, inputSize);

    // Program answer
    FILE* testAnswerFile = fopen("./answer.txt", "r");

    fseek(inputFile, SEEK_SET, SEEK_SET);
    EXPECT_EQ(true, check_if_eq_files(answerFile, testAnswerFile));
    fclose(inputFile);
    fclose(answerFile);
    fclose(testAnswerFile);
}

TEST(General, general_test3) {
    FILE* inputFile = fopen("./Google_tests/tests/test3.txt", "r");
    FILE* answerFile = fopen("./Google_tests/answers/answer3.txt", "r");
    size_t inputSize = 0;

    // Logic
    Skyscraper* skyscrapers = input(inputFile, &inputSize);
    group_by_purpose(skyscrapers, inputSize);
    output_scyscrapers_in_file(skyscrapers, inputSize);
    free_skyscrapers(skyscrapers, inputSize);

    // Program answer
    FILE* testAnswerFile = fopen("./answer.txt", "r");

    fseek(inputFile, SEEK_SET, SEEK_SET);
    EXPECT_EQ(true, check_if_eq_files(answerFile, testAnswerFile));
    fclose(inputFile);
    fclose(answerFile);
    fclose(testAnswerFile);
}

TEST(General, general_test4) {
    FILE* inputFile = fopen("./Google_tests/tests/test4.txt", "r");
    FILE* answerFile = fopen("./Google_tests/answers/answer4.txt", "r");
    size_t inputSize = 0;

    // Logic
    Skyscraper* skyscrapers = input(inputFile, &inputSize);
    group_by_purpose(skyscrapers, inputSize);
    output_scyscrapers_in_file(skyscrapers, inputSize);
    free_skyscrapers(skyscrapers, inputSize);

    // Program answer
    FILE* testAnswerFile = fopen("./answer.txt", "r");

    fseek(inputFile, SEEK_SET, SEEK_SET);
    EXPECT_EQ(true, check_if_eq_files(answerFile, testAnswerFile));
    fclose(inputFile);
    fclose(answerFile);
    fclose(testAnswerFile);
}

TEST(General, general_test5) {
    FILE* inputFile = fopen("./Google_tests/tests/test5.txt", "r");
    FILE* answerFile = fopen("./Google_tests/answers/answer5.txt", "r");
    size_t inputSize = 0;

    // Logic
    Skyscraper* skyscrapers = input(inputFile, &inputSize);
    group_by_purpose(skyscrapers, inputSize);
    output_scyscrapers_in_file(skyscrapers, inputSize);
    free_skyscrapers(skyscrapers, inputSize);

    // Program answer
    FILE* testAnswerFile = fopen("./answer.txt", "r");

    fseek(inputFile, SEEK_SET, SEEK_SET);
    EXPECT_EQ(true, check_if_eq_files(answerFile, testAnswerFile));
    fclose(inputFile);
    fclose(answerFile);
    fclose(testAnswerFile);
}