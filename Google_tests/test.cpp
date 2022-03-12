#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "skyscraperio.h"
}

TEST(Equals, Equals_E_Test) {
    // ASSERT_EQ // Приведет к падению теста сразу
    // EXPECT_EQ // Продолжит тест, но потом уведомит что тест тут упал

    // // fmemopen "меням работу с строчкой на работу с файлом"
    // Skyscraper* skyscraper1;
    // Skyscraper* skyscraper2;
    // char* myStr1 = "test";
    // input_scyscraper(skyscraper1, 2, 2, 2, myStr1, myStr1);
    // input_scyscraper(skyscraper2, 2, 2, 2, myStr1, myStr1);
    EXPECT_EQ(1, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}