#include "IGumboNodeVisitor.h"
#include "../NodePredicates.h"

void IGumboNodeVisitor::iterate(GumboNode* node) {
    if (node == nullptr) {
        return;
    }

    if (!Predicates::IsNode(node)) {
        return;
    }

    //Only visit the node, if it was present in the raw html
    if ((node->parse_flags & GUMBO_INSERTION_BY_PARSER) == 0) {
        visit(node);
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        iterate(static_cast<GumboNode*>(children->data[i]));
    }
}