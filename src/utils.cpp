#include <mutex>
#include <thread>
#include <fstream>

#include "utils.h"


std::vector<std::string> ReadUrlsFromFile(const std::string& filePath)
{
    std::ifstream infile(filePath);
    std::vector<std::string> urls;
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line))
        {
            urls.push_back(line);
        }
    }

    return urls;
}


namespace {

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

}

std::string MakeHttpRequest(const std::string& url) {
    //Source: https://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
        curl_easy_cleanup(curl);

    }
    return readBuffer;
}

static std::mutex s_mtx;
void logger(const std::string& s) {
    std::unique_lock<std::mutex> lk(s_mtx);
    std::cout << std::this_thread::get_id() << " - " << s << std::endl;
}
