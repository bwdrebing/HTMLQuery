#include <gtest/gtest.h>


int main(int ac, char* av[]) {
    ::testing::InitGoogleTest();
    int retVal = RUN_ALL_TESTS();
    getchar();
    return retVal;
}