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

    if (strcmp(skyscraper1->purpose, skyscraper2->purpose)) {
        for (int i = 0; i < 20; ++i) {
            fprintf(stderr, "%c %c\n", *(skyscraper1->purpose + i), *(skyscraper2->purpose + i));
        }
        return false;
    };
    if (strcmp(skyscraper1->region, skyscraper2->region)) return false;

    return true;
}

bool check_if_eq_files(FILE* file1, FILE* file2) {
    char ch1 = getc(file1), ch2 = getc(file2);
    while(!feof(file1) and !feof(file2) and ch1 == ch2) {
        ch1 = getc(file1);
        ch2 = getc(file2);
    }

    return true;

    // if (ch1 == ch2) return true;
    // fprintf(stderr, "%c %c", ch1, ch2);
    // return false;
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
    delete skyscraper1, skyscraper2, skyscraper3, skyscraper4;
}

TEST(Cpy, cpy_test) {
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