#include <gtest/gtest.h>

#include "HtmlQueryEngine.h"
#include "utils.h"

TEST(HtmlQueryEngine, MoreThreadsThanUrls) {

    std::vector<std::string> urlsToSearch = {
        "https://en.cppreference.com/w/cpp/thread/mutex",
        "https://en.cppreference.com/w/cpp/thread/unique_lock",
        "https://en.cppreference.com/w/cpp/thread/condition_variable",
        "https://en.cppreference.com/w/cpp/thread/async"
    };

    HtmlQueryEngine engine({&Predicates::IsNode, &Predicates::IsDiv, &Predicates::IsLeaf});
    engine.processUrls(urlsToSearch, 6);
    for (const auto& url : urlsToSearch) {
        EXPECT_FALSE(engine.getResults(url).empty());
    }
}

TEST(HtmlQueryEngine, DuplicateUrls) {

    std::vector<std::string> urlsToSearch = {
        "https://en.cppreference.com/w/cpp/thread/mutex",
        "https://en.cppreference.com/w/cpp/thread/unique_lock",
        "https://en.cppreference.com/w/cpp/thread/mutex",
        "https://en.cppreference.com/w/cpp/thread/unique_lock"
    };

    HtmlQueryEngine engine({ &Predicates::IsNode, &Predicates::IsDiv, &Predicates::IsLeaf });
    engine.processUrls(urlsToSearch, 5);
    for (const auto& url : urlsToSearch) {
        EXPECT_FALSE(engine.getResults(url).empty());
    }
}
