#ifndef INDEX_H
#define INDEX_H

#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <cstdlib>
#include <iostream>

class TIndex {
public:
    void IndexAll(std::string &inputName);
    void Print();
    void SaveIndexes(std::string &outputName);
    void LoadIndexes(std::string &indexName);
    bool HasWord(const std::wstring &word);

    friend class TQueries;

private:
    bool GetName(std::wifstream &input);
    void Index(uint32_t n, std::wifstream &input);
    std::vector<std::wstring> names;
    std::unordered_map<std::wstring, std::vector<uint32_t>> indexes;
    uint32_t textsCnt;
};

#endif
