#include "NodePredicates.h"

bool Predicates::IsNode(GumboNode* node)
{
    return node->type == GUMBO_NODE_ELEMENT;
}

