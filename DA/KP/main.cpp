#include <locale>
#include <iostream>

#include "TIndex.h"

int main(int argc, char *argv[]) {
    std::string inputName;
    std::string outputName;
    TIndex index;
    
    // TODO Locale

    // TODO Query-parser

    // ./kp inputName outputName
    if (argc =! 3) {
        std::cout << "Usage: ./kp inputName outputName" << std::endl;
        return EXIT_FAILURE;
    }
    
    inputName = argv[1];
    outputName = argv[2];

    index.IndexAll(inputName);
    index.Print();

    return EXIT_SUCCESS;
}