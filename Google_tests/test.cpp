#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "skyscraperio.h"
}

TEST(Inputs, Input_errors_NULL_str) {
    char str[] = "test";
    char test[] = "\0";
    Skyscraper* skyscraper = (Skyscraper*)malloc(sizeof(Skyscraper));
    EXPECT_EQ(0, input_scyscraper(NULL, 2, 2, 2, str, str));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, NULL, NULL));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, str, NULL));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, NULL, str));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, str, test));
    EXPECT_EQ(0, input_scyscraper(skyscraper, 2, 2, 2, test, str));
    free(skyscraper);
}

bool check_if_eq(Skyscraper* skyscraper1, Skyscraper* skyscraper2) {
    if (skyscraper1->numberOfFloors != skyscraper2->numberOfFloors ||
        skyscraper1->overallHeight != skyscraper2->overallHeight ||
        skyscraper1->spireHeight != skyscraper2->spireHeight) {
            return false;
        }

    if (strcmp(skyscraper1->region, skyscraper2->region)) return false;

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

TEST(Inputs, Inputs_logic) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper3 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper4 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char myStr1[] = "test";

    input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    input_scyscraper(skyscraper2, 2, 2, 2, myStr1, myStr1);
    input_scyscraper(skyscraper3, 3, 5, 3, myStr1, myStr1);
    input_scyscraper(skyscraper4, 2, 2, 2, myStr1, myStr1);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(false, check_if_eq(skyscraper1, skyscraper3));
    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper4));

    free(skyscraper1);
    free(skyscraper2);
    free(skyscraper3);
    free(skyscraper4);
}

TEST(Inputs, Input_from_file) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper3 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper4 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char buffer[] = "163 828 100 Residential Europe";
    FILE* file = fmemopen(buffer, strlen(buffer), "r");

    size_t size;
    size = 0;
    skyscraper1 = input(file, &size);

    char purpose[] = "Residential";
    char region[] = "Europe";
    input_scyscraper(skyscraper2, 163, 828, 100, purpose, region);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
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
    free(skyscraper1);
    free(skyscraper2);
    free(skyscraper3);
    free(skyscraper4);
}

TEST(Cpy, cpy_test) {
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char myStr1[] = "test";

    input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    copy_skyscrapers(skyscraper2, skyscraper1);

    EXPECT_EQ(true, check_if_eq(skyscraper1, skyscraper2));
    EXPECT_EQ(false, copy_skyscrapers(skyscraper2, NULL));
    EXPECT_EQ(false, copy_skyscrapers(NULL, skyscraper2));
    
    free(skyscraper1);
    free(skyscraper2);
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