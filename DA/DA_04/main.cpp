#include <iostream>
#include "Parse.h"
#include "KMP.h"

int main() {

    // Text parsing
    std::vector<std::string> pattern = PatternParse();

    // KMP work
    Kmp(pattern);

    return 0;
}