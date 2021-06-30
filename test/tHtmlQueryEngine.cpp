#include <gtest/gtest.h>

#include "HtmlQueryEngine.h"
#include "utils.h"

TEST(HtmlQueryEngine, ManyUrls) {

    std::vector<std::string> urlsToSearch = ReadUrlsFromFile("assets/ManyUrls");

    HtmlQueryEngine engine({&Predicates::IsNode, &Predicates::IsDiv, &Predicates::IsLeaf});
    engine.processUrls(urlsToSearch, 2);
    for (const auto& url : urlsToSearch) {
        EXPECT_FALSE(engine.getResults(url).empty());
    }
}