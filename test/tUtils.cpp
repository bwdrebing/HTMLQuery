#include <gtest/gtest.h>

#include "utils.h"

TEST(UtilsTest, BadFileNameReturnsNoUrls) {
    auto urls = ReadUrlsFromFile("BadFileName.txt");
    EXPECT_TRUE(urls.empty());
}