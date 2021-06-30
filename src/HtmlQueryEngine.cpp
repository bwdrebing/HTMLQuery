#include <future>
#include <gumbo.h>
#include <iomanip>

#include "HtmlQueryEngine.h"
#include "utils.h"
#include "visitors/CountingVisitor.h"

using namespace std;

HtmlQueryEngine::HtmlQueryEngine(const std::vector<NodePredicate>& preds)
:m_predicates(preds) {

}

void HtmlQueryEngine::processUrls(const std::vector<std::string> vecUrls, size_t numThreads) {
    for (size_t i = 0; i < vecUrls.size(); i++) {
        m_urls.push_back(vecUrls[i]);
        m_urlsLeftToProcess.push(vecUrls[i]);
    }

    std::vector<std::future<void>> futures;
    for (size_t i = 0; i < numThreads; i++) {
        futures.push_back(std::async(std::launch::async, &HtmlQueryEngine::threadProc, this, i));
    }
    {

        std::unique_lock<mutex> lk(m_mtxMapAccess);
        m_cv.wait(lk, [&]{
            logger("Checking if done");
            return m_mapOfResults.size() == m_urls.size();
        });
    }

}

std::vector<size_t> HtmlQueryEngine::getResults(const std::string& url) const {
    auto results = m_mapOfResults.find(url);
    if (results == m_mapOfResults.end()) {
        return {};
    }
    else {
        return results->second;
    }
}

void HtmlQueryEngine::threadProc(size_t id)
{
   logger("Spinning up");
    while (true) {
        string urlToProcess = "";
        {
            std::unique_lock<mutex> lk(m_mtxQueueAccess);
            if (m_urlsLeftToProcess.empty()) {
                break;
            }
            urlToProcess = m_urlsLeftToProcess.front();
            m_urlsLeftToProcess.pop();
        }
        logger("Processing " + urlToProcess);
        string urlContents = "";
        {
            std::unique_lock<mutex> lk(m_mtxNetworkAccess);
            urlContents = MakeHttpRequest(urlToProcess);
        }

        GumboOutput* output = gumbo_parse(urlContents.c_str());
        CountingVisitor visitor(m_predicates);
        visitor.iterate(output->root);
        gumbo_destroy_output(&kGumboDefaultOptions, output);

        {
            std::unique_lock<mutex> lk(m_mtxMapAccess);
            m_mapOfResults[urlToProcess] = visitor.getResults();
            logger("Signal work complete");
        }
        m_cv.notify_one();
    }
}

