#include <vector>
#include <queue>
#include <map>
#include <mutex>

#include <iostream>

#include "NodePredicates.h"

class HtmlQueryEngine {
public:
    HtmlQueryEngine(const std::vector<NodePredicate>& preds);
    void processUrls(const std::vector<std::string> vecUrls, size_t numThreads);
    std::vector<size_t> getResults(const std::string& url) const;

private:

    void threadProc(size_t id);
    std::vector<size_t> queryHtml(const std::string& content) const;
    bool allUrlsProcessed() const;

    std::vector<NodePredicate> m_predicates;
    std::vector<std::string> m_urls;
    std::queue<std::string> m_urlsLeftToProcess;
    std::map<std::string,std::vector<size_t>> m_mapOfResults;

    std::mutex m_mtxQueueAccess;
    std::mutex m_mtxNetworkAccess;
    std::mutex m_mtxMapAccess;

    std::condition_variable m_cv;



};