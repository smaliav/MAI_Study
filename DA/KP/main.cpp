#include <locale>
#include <iostream>
#include <cstring>

#include "Index.h"
#include "Query.h"

bool CheckIndexFlags(char *argv[]) {
    if (!std::strcmp(argv[1], "index") && !std::strcmp(argv[2], "--input") &&
        !std::strcmp(argv[4], "--output")) {
        return true;
    }
    else {
        return false;
    }
}

bool CheckSearchFlags(char *argv[]) {
    if (!std::strcmp(argv[1], "search") && !std::strcmp(argv[2], "--index") &&
        !std::strcmp(argv[4], "--input") && !std::strcmp(argv[6], "--output")) {
        return true;
    }
    else {
        return false;
    }
}

void UsageHelper() {
    std::cout << "usage:" << std::endl;
    std::cout << "./prog index --input <input file> --output <index file>" << std::endl;
    std::cout << "./prog search --index <index file> --input <input file> --output <output file> [--full-output]" << std::endl;
}

int main(int argc, char *argv[]) {
    std::locale::global(std::locale("en_US.UTF-8"));
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale());
    std::wcout.imbue(std::locale());

    std::string inputName;
    std::string outputName;
    std::string indexName;

    if (argc == 6) {
        if (CheckIndexFlags(argv)) {
            TIndex idx;
            inputName = argv[3];
            outputName = argv[5];

            std::cout << "Indexation STARTED" << std::endl;
            idx.IndexAll(inputName);
            std::cout << "Indexation COMPLETED" << std::endl;
            std::cout << "Saving indexes STARTED" << std::endl;
            idx.SaveIndexes(outputName);
            std::cout << "Saving indexes COMPLETED" << std::endl;
        }
    }
    else if (argc == 8 || argc == 9) {
        if (CheckSearchFlags(argv)) {
            indexName = argv[3];
            inputName = argv[5];
            outputName = argv[7];

            TIndex idx;
            idx.LoadIndexes(indexName);
            TQueries queries(inputName);
            queries.Search(indexName, idx);

            if (argc == 9 && !std::strcmp(argv[8], "--full-output")) {
                queries.SaveSearchFull(outputName, idx);
            }
            else {
                queries.SaveSearch(outputName);
            }
        }
    }
    else {
        UsageHelper();
    }

    return 0;
}