#include "CountingVisitor.h"

CountingVisitor::CountingVisitor(const std::vector<NodePredicate>& preds)
    : m_predicates(preds) { 
    for (size_t i = 0; i < m_predicates.size(); i++) {
        m_counts.push_back(0);
    }
}

void CountingVisitor::visit(GumboNode* node) {
    if (node == nullptr) {
        return;
    }

    for (size_t i = 0; i < m_predicates.size(); i++) {
        if (m_predicates[i](node)) {
            m_counts[i] = m_counts[i] + 1;
        }
    }
}

std::vector<size_t> CountingVisitor::getResults()
{
    return m_counts;
}

