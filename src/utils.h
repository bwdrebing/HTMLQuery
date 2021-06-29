#include <iostream>
#include <string>
#include <curl/curl.h>
#include <gumbo.h>

std::string MakeHttpRequest(const std::string& url);

void logger(const std::string& s);