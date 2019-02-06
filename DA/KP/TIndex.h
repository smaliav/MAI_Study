#ifndef INDEX_H
#define INDEX_H

#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <fstream>

class TIndex {
public:
    void IndexAll(std::string &inputName);
    bool GetName(std::wifstream &input);
    void Print();

private:
    void Index(uint32_t n, std::wifstream &input);
    std::vector<std::wstring> names;
    std::unordered_multimap<std::wstring, uint32_t> indexes;
};

#endif