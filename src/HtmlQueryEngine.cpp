#include <future>
#include <gumbo.h>

#include "HtmlQueryEngine.h"
#include "utils.h"

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
        //Do Something
        gumbo_destroy_output(&kGumboDefaultOptions, output);

    }
}

