#include <iostream>
#include <string>
#include <vector>

#include "utils.h"
#include "HtmlQueryEngine.h"

using namespace std;
int main(int argc, const char** argv)
{
    if (argc != 3) {
        std::cerr << "Incorrect number of arguments. 2 arguments expected." <<std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    
    size_t numThreads = 0;
    try {
        numThreads = std::stoi(argv[2]);
    }
    catch (...) {
        std::cerr << "Failed to parse second argument. It must be an integer." <<std::endl;
        return 1;
    }


    std::vector<string> urlsToSearch = ReadUrlsFromFile(filePath);

    HtmlQueryEngine engine({&Predicates::IsNode, &Predicates::IsDiv, &Predicates::IsLeaf});
    engine.processUrls(urlsToSearch,1);
    engine.output();
    return 0;
}
