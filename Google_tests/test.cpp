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

TEST(Equals, Equals_E_Test) {
    // ASSERT_EQ // Приведет к падению теста сразу
    // EXPECT_EQ // Продолжит тест, но потом уведомит что тест тут упал

    // // fmemopen "меням работу с строчкой на работу с файлом"
    Skyscraper* skyscraper1 = (Skyscraper*)malloc(sizeof(Skyscraper));
    Skyscraper* skyscraper2 = (Skyscraper*)malloc(sizeof(Skyscraper));

    char* myStr1 = (char*)malloc(4);
    strcpy(myStr1, "test");
    input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    input_scyscraper(skyscraper2, 2, 2, 2, myStr1, myStr1);

    cpy(skyscraper2, skyscraper1);
    EXPECT_EQ(skyscraper1, skyscraper2);

    delete myStr1;
}