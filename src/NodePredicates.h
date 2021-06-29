#include <functional>

#include <gumbo.h>

typedef std::function<bool(GumboNode*)> NodePredicate;

namespace Predicates {
    bool IsNode(GumboNode* node);
}
