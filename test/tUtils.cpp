#include <gtest/gtest.h>

#include "utils.h"

TEST(UtilsTest, ReadingUrlsFromFile) {
    auto urls = ReadUrlsFromFile("assets/ManyUrls.txt");
    EXPECT_EQ(urls.size(), 7);
}

TEST(UtilsTest, BadFileNameReturnsNoUrls) {
    auto urls = ReadUrlsFromFile("BadFileName.txt");
    EXPECT_TRUE(urls.empty());
}