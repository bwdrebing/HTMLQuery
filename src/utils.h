#include <iostream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <gumbo.h>

std::vector<std::string> ReadUrlsFromFile(const std::string& fileContents);

std::string MakeHttpRequest(const std::string& url);

void PrintQueryResults(const std::string& url, std::vector<size_t> results);

void logger(const std::string& s);