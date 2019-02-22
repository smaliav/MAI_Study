#include "Query.h"

TQueries::TQueries() {}

std::wstring StringToWstring(const std::string &t_str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    return converter.from_bytes(t_str);
}

TQueries::TQueries(std::string &inputName) {
    std::wifstream input((inputName).c_str());
    std::wstring query;

    while (std::getline(input, query)) {
        MakeRPN(query);
    }
}

void TQueries::MakeRPN(std::wstring &query) {
    std::stack<wchar_t> signStack;
    std::wstring word;
    std::vector<std::wstring> parsedQuery;
    wchar_t topSym;

    for (wchar_t sym: query) {
        if (sym == '~') {
            signStack.push(sym);
        }
        else if (sym == '&') {
            if (signStack.empty()) {
                signStack.push(sym);
                continue;
            }

            topSym = signStack.top();
            while (topSym == '~' || topSym == '&') {
                word.push_back(topSym);
                signStack.pop();
                if (!signStack.empty()) {
                    topSym = signStack.top();
                }
                else {
                    break;
                }
            }
            signStack.push(sym);
            if (!word.empty()) {
                parsedQuery.push_back(word);
                word.clear();
            }
        }
        else if (sym == '|') {
            if (signStack.empty()) {
                signStack.push(sym);
                continue;
            }

            topSym = signStack.top();

            while (topSym == '~' || topSym == '&' || topSym == '|') {
                word.push_back(topSym);
                signStack.pop();
                if (!signStack.empty()) {
                    topSym = signStack.top();
                }
                else {
                    break;
                }
            }
            signStack.push(sym);
            if (!word.empty()) {
                parsedQuery.push_back(word);
                word.clear();
            }
        }
        else if (sym == '(') {
            signStack.push(sym);
        }
        else if (sym == ')') {
            if (!word.empty()) {
                parsedQuery.push_back(word);
                word.clear();
            }
            topSym = signStack.top();

            while (topSym != '(') {
                word.push_back(topSym);
                signStack.pop();
                if (!signStack.empty()) {
                    topSym = signStack.top();
                }
                else {
                    break;
                }
            }
            signStack.pop();
            if (!word.empty()) {
                parsedQuery.push_back(word);
                word.clear();
            }
        }
        else if (sym == ' ') {
            if (!word.empty()) {
                parsedQuery.push_back(word);
                word.clear();
            }
        }
        else {
            word.push_back(sym);
        }
    }
    if (!word.empty()) {
        parsedQuery.push_back(word);
        word.clear();
    }

    while (!signStack.empty()) {
        word.push_back(signStack.top());
        parsedQuery.push_back(word);
        signStack.pop();
        word.clear();
    }

    queries.push_back(parsedQuery);
}

void TQueries::PrintParsedQueries() {
    for (const auto &query: this->queries) {
        for (const std::wstring &word: query) {
            std::wcout << word << L" ";
        }
        std::wcout << std::endl;
    }
}

void TQueries::Search(std::string &indexName, TIndex &idx) {
    std::vector<uint32_t> tmpSet;
    std::vector<uint32_t> workSet1;
    std::vector<uint32_t> workSet2;
    std::stack<std::vector<uint32_t>> setsStack;
    std::vector<uint32_t> allTextsSet;

    for (uint32_t i = 1; i <= idx.textsCnt; ++i) {
        allTextsSet.push_back(i);
    }

    // Run through query expressions in RPN
    // Making operations with sets of matching texts
    for (const auto &query: queries) {
        for (const auto &elem: query) {
            if (elem == L"&") {
                // Intersection of sets
                workSet1 = setsStack.top();
                setsStack.pop();
                workSet2 = setsStack.top();
                setsStack.pop();
                tmpSet.resize(std::max(workSet1.size(), workSet2.size()));

                auto it = std::set_intersection(workSet1.begin(), workSet1.end(),
                                        workSet2.begin(), workSet2.end(),
                                        tmpSet.begin());
                tmpSet.resize(it - tmpSet.begin());

                setsStack.push(tmpSet);
                workSet1.clear();
                workSet2.clear();
                tmpSet.clear();
            }
            else if (elem == L"|") {
                // Union of sets
                workSet1 = setsStack.top();
                setsStack.pop();
                workSet2 = setsStack.top();
                setsStack.pop();
                tmpSet.resize(workSet1.size() + workSet2.size());

                auto it = std::set_union(workSet1.begin(), workSet1.end(),
                                                workSet2.begin(), workSet2.end(),
                                                tmpSet.begin());
                tmpSet.resize(it - tmpSet.begin());

                setsStack.push(tmpSet);
                workSet1.clear();
                workSet2.clear();
                tmpSet.clear();
            }
            else if (elem == L"~") {
                // Difference of sets

                workSet1 = setsStack.top();
                setsStack.pop();
                tmpSet.resize(allTextsSet.size());

                auto it = std::set_difference(allTextsSet.begin(), allTextsSet.end(),
                                                workSet1.begin(), workSet1.end(),
                                                tmpSet.begin());

                tmpSet.resize(it - tmpSet.begin());

                setsStack.push(tmpSet);
                workSet1.clear();
                tmpSet.clear();
            }
            else {
                // See word, add texts to set, then set to stack
                tmpSet.assign(idx.indexes[elem].begin(), idx.indexes[elem].end());
                setsStack.push(tmpSet);
                tmpSet.clear();
            }
        }

        this->results.push_back(setsStack.top());

        while (!setsStack.empty()) {
            setsStack.pop();
        }
    }
}

void TQueries::SaveSearch(std::string &outputName) {
    std::wofstream out(outputName.c_str());

    if (out) {
        for (const auto &queryRes: results) {
            out << queryRes.size() << std::endl;
        }
    }
}

void TQueries::SaveSearchFull(std::string &outputName, TIndex &idx) {
    std::wofstream out(outputName.c_str());

    if (out) {
        for (const auto &queryRes: results) {
            out << queryRes.size() << std::endl;

            for (const auto &txtNum: queryRes) {
                out << idx.names[txtNum - 1] << std::endl;
            }
        }
    }
}
