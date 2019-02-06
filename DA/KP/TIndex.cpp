#include "TIndex.h"

void TIndex::IndexAll(std::string &inputName) {
    uint32_t cnt = 1;
    std::wifstream input((inputName).c_str());
    
    while (GetName(input)) {
        // DEBUG PRINT
        std::cout << "TEXT: " << cnt << std::endl;
        // DEBUG PRINT
        Index(cnt, input);
        ++cnt;
    }

    input.close();
}

void TIndex::Index(uint32_t n, std::wifstream &input) {
    std::wstring str, tmp;
    std::unordered_set<std::wstring> words;
    std::wstring end = L"</doc>";
    bool flag = false;
  
    int tmpCtr = 1;

    do {
        std::getline(input, str);
        
        if (str == end) {
            break;
        }
    
        for (uint32_t i = 0; i < str.length(); ++i) {
            if (isalnum(str[i], std::locale())) {
                flag = true;
                tmp.push_back(std::tolower(str[i], std::locale()));
            }
            else if (flag) {
                words.insert(tmp);
                flag = false;
                tmp.clear();
            }
        }
        
        if (flag) {
            words.insert(tmp);
            flag = false;
            tmp.clear();
        }
        
        std::cout << tmpCtr << std::endl;
        ++tmpCtr;
    } while (str != end);
  
    for (auto &it: words) {
        indexes.insert(std::make_pair(it, n));
    }
}

bool TIndex::GetName(std::wifstream &input) {
    std::wstring str;
  
    // Get <doc id="..." url="..." title="..."> line
    while (!str.size()) {
        if (input.eof()) {
            return false;
        }
        std::getline(input, str);
    }
  
    uint32_t k = 0;
    uint32_t cnt = 0;
    uint32_t i = str.length() - 1;
  
    while (cnt != 2) {
        if (str[i] == '\"') {
            cnt++;
        }
        else if (cnt == 1) {
            ++k;
        }
        --i;
    }
  
    i += 2;
    names.push_back(str.substr(i, k));
    return true;
}

void TIndex::Print() {
    for (auto it = this->indexes.begin(); it != this->indexes.end(); it++) {
        std::wcout << it->first << " " << it->second << std::endl;
    }
}
