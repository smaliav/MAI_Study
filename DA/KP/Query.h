#ifndef QUERIES_H
#define QUERIES_H

#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
#include <set>
#include <codecvt>
#include <locale>

#include "Index.h"

class TQueries {
public:
    TQueries();
    TQueries(std::string &inputName);
    void PrintParsedQueries();
    void Search(std::string &indexName, TIndex &idx);
    void SaveSearch(std::string &outputName);
    void SaveSearchFull(std::string &outputName, TIndex &idx);

private:
    void MakeRPN(std::wstring &input);              // Makes Reverse Polish Notation from query

    std::vector<std::vector<std::wstring>> queries; // All queries in Reverse Polish Notation
    std::vector<std::vector<uint32_t>> results;     // Numbers of match texts for each query
};

#endif // QUERIES_H
