#include <gtest/gtest.h>
#include <iostream>
#include <ostream>

#include "visitors/CountingVisitor.h"

TEST(CountingVisitor, DeeplyNestedDivs) {
    std::ostringstream os;
    size_t numDivs = 1000;
    for (size_t i = 0; i < numDivs; i++) {
        os << "<div>";
    }
    os << "Hi there";
    for (size_t i = 0; i < numDivs; i++) {
        os << "</div>";
    }
    
    GumboOutput* output = gumbo_parse(os.str().c_str());
    CountingVisitor visitor({&Predicates::IsDiv, &Predicates::IsLeaf});
    visitor.iterate(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    auto results = visitor.getResults();
    EXPECT_EQ(results.size(),2);
    EXPECT_EQ(results[0],numDivs);
    EXPECT_EQ(results[1],1) << "There should only be one leaf node";

}

TEST(CountingVisitor, CommentsAndTextAreNotNodes) {
    std::ostringstream os;
    
    os << "<div>";
    os << "Hi I'm some text...";
    os << "<!-- I'm a comment -->";
    os << "</div>";
    

    GumboOutput* output = gumbo_parse(os.str().c_str());
    CountingVisitor visitor({ &Predicates::IsNode, &Predicates::IsLeaf });
    visitor.iterate(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    auto results = visitor.getResults();
    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], 1) << "There should be only one node, text and comments don't count.";
    EXPECT_EQ(results[1], 1) << "The div should count as a leaf node, regardless of child text or comments.";

}
