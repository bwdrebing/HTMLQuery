#include <functional>

#include <gumbo.h>

typedef std::function<bool(GumboNode*)> NodePredicate;

namespace Predicates {
    bool IsNode(GumboNode* node);
    bool IsDiv(GumboNode* node);
    bool IsLeaf(GumboNode* node);
    bool PrettyPrinter(GumboNode* node);

}
