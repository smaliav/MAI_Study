#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

    void Kmp(std::vector<std::string>& pat);
    std::vector<int> Zfunc(std::vector<std::string>& pat);
    std::vector<int> CalcSP(std::vector<int>& z, std::vector<std::string>& pat);
    std::vector<int> FailFunction(std::vector<std::string>& pattern);

#endif /* KMP_H */