#include "IGumboNodeVisitor.h"

#include <vector>
#include "../NodePredicates.h"


class CountingVisitor : public IGumboNodeVisitor {
public:
    CountingVisitor(const std::vector<NodePredicate>& preds);
    void visit(GumboNode* node) override;
    std::vector<size_t> getResults();
private:
    std::vector<NodePredicate> m_predicates;
    std::vector<size_t> m_counts;
};