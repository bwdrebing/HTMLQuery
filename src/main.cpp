#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "HtmlQueryEngine.h"

using namespace std;
int main(int argc, const char** argv)
{
   
    std::vector<string> urlsToSearch{
        "http://localhost:8000/1.html",
        "http://localhost:8000/2.html",
        "http://localhost:8000/3.html",
        "http://localhost:8000/4.html",
        "http://localhost:8000/5.html",
    };

    HtmlQueryEngine engine({&Predicates::IsNode});
    engine.processUrls(urlsToSearch,3);
    engine.output();
    return 0;
}
