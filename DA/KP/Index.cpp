#include <set>
#include "Index.h"

std::wstring RemoveCommas(std::wstring &str) {
    std::wstring res;

    for (wchar_t &sym: str) {
        if (sym == ',') {
            continue;
        }
        else {
            res.push_back(sym);
        }
    }

    return res;
}

void TIndex::IndexAll(std::string &inputName) {
    uint32_t cnt = 1;
    std::wifstream input((inputName).c_str());

    while (GetName(input)) {
        Index(cnt, input);
        std::cout << "--> Text " << cnt << " DONE" << std::endl;
        ++cnt;
    }

    textsCnt = this->names.size();
    input.close();
}

void TIndex::Index(uint32_t n, std::wifstream &input) {
    std::wstring str, tmp;
    std::unordered_set<std::wstring> words;
    std::wstring end = L"</doc>";
    bool gettingWord = false;

    while (std::getline(input, str)) {

        if (str == end) {
            break;
        }

        for (uint32_t i = 0; i < str.length(); ++i) {
            if (isalnum(str[i], std::locale())) {
                gettingWord = true;
                tmp.push_back(std::tolower(str[i], std::locale()));
            }
            else if (gettingWord) {
                words.insert(tmp);
                gettingWord = false;
                tmp.clear();
            }
        }

        if (gettingWord) {
            words.insert(tmp);
            gettingWord = false;
            tmp.clear();
        }
    }

    // for (const std::wstring &it: words) {
    //     auto i = indexes.find(it);
    //     if (i != indexes.end()) {
    //         indexes[it].push_back(n);
    //     }
    //     else {
    //         indexes.insert(std::make_pair(it, std::vector<uint32_t>(1, n)));
    //     }
    // }
    for (const std::wstring &it: words) {
        indexes[it].push_back(n);
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
        std::wcout << it->first << " ";
        for (uint32_t &textNum: it->second) {
            std::wcout << textNum << " ";
        }
        std::wcout << std::endl;
    }
}

void TIndex::SaveIndexes(std::string &outputName) {
    std::wofstream out((outputName).c_str());
    if (out) {
        out << textsCnt << std::endl;

        for (const auto &txtName: names) {
            out << txtName << std::endl;
        }

        std::cout << "--> Texts names SAVED" << std::endl;

        for (const auto &it: indexes) {
            out << it.first << " ";
            for (const auto &elem: it.second) {
                out << elem << " ";
            }
            out << std::endl;
        }

        std::cout << "--> Indexes SAVED" << std::endl;
    }
    out.close();
}

void TIndex::LoadIndexes(std::string &indexName) {
    std::wifstream input(indexName.c_str());
    std::wstring wStr;
    std::wstring word;
    std::wstring num;
    std::vector<uint32_t> texts;
    bool gotWord = false;

    if (input) {
        std::getline(input, wStr);
        wStr = RemoveCommas(wStr);
        textsCnt = std::stoll(wStr); // Reading count of texts

        for (int i = 0; i < textsCnt; ++i) {
            std::getline(input, wStr);
            names.push_back(wStr);
        }

        while (std::getline(input, wStr)) {
            for (wchar_t &sym: wStr) {
                if (sym == ' ' && !gotWord) {
                    gotWord = true;
                }
                else if (sym == ' ') {
                    if (!num.empty()) {
                        texts.push_back(std::stoll(num));
                        num.clear();
                    }
                }
                else if (!gotWord) {
                    word.push_back(sym);
                }
                else {
                    num.push_back(sym);
                }
            }
            indexes.insert(std::make_pair(word, texts));
            gotWord = false;
            word.clear();
            texts.clear();
        }
    }
}

bool TIndex::HasWord(const std::wstring &word) {
    if (this->indexes.find(word) != this->indexes.end()) {
        return true;
    }
    else {
        return false;
    }
}
