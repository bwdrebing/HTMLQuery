#include "NodePredicates.h"

bool Predicates::IsNode(GumboNode* node)
{
    return node->type == GUMBO_NODE_ELEMENT;
}

bool Predicates::IsDiv(GumboNode* node)
{
    if (!IsNode(node)) {
        return false;
    }

    if (node->v.element.tag == gumbo_tag_enum("div")) {
        return true;
    }
    return false;
}

bool Predicates::IsLeaf(GumboNode* node) {
    if (!IsNode(node)) {
        return false;
    }

    //Now check if node has any node children...
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        GumboNode* child = static_cast<GumboNode*>(children->data[i]);
        if (IsNode(child)) {
            return false;
        }
    }
    return true;
}

