#include "KMP.h"

std::vector<int> Zfunc(std::vector<std::string>& pat) {
    const unsigned long n = pat.size();
    std::vector<int> zArray(n);

    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            zArray[i] = std::min(r - i + 1, zArray[i - l]);
        }
        while (i + zArray[i] < n && pat[zArray[i]] == pat[i + zArray[i]]) {
            ++zArray[i];
        }
        if (i + zArray[i] - 1 > r) {
            l = i; r = i + zArray[i] - 1;
        }
    }

    return zArray;
}

std::vector<int> CalcSP(std::vector<int>& zArray, std::vector<std::string>& pat) {
    const unsigned long n = pat.size(); // Number of symbols in the pattern
    std::vector<int> spArray(n);

    for (unsigned long j = n - 1; j > 0; --j) {
        unsigned long i = j + zArray[j] - 1;
        spArray[i] = zArray[j];
    }

    return spArray;
}

std::vector<int> FailFunction(std::vector<std::string>& pattern) {
    unsigned long n = pattern.size();

    std::vector<int> zArray = Zfunc(pattern);
    std::vector<int> spArray = CalcSP(zArray, pattern);

    std::vector<int> f(n + 1);
    f[0] = 0;
    for (int k = 1; k < n; ++k) {
        f[k] = spArray[k - 1];
    }
    f[n] = spArray[n - 1];

    return f;
}

void Kmp(std::vector<std::string>& pat) {
    std::vector<std::pair<std::pair<int, int>, std::string>> text;

    char c = '!';                                       // Current symbol, ! - only to initialize
    bool wordAdded = true;                              // True if last action was to add the word into the vector
    std::pair<std::pair<int, int>, std::string> temp;   // Temporary container
    unsigned long n = pat.size();                       // Pattern size
    temp.first.first = 1;                               // Row counter
    temp.first.second = 1;                              // Word counter
    int p = 0;                                          // Pattern pointer
    int t = 0;                                          // Text pointer

    std::vector<int> f = FailFunction(pat);

    do {
        while (text.size() < pat.size() && c != EOF) {
            c = getchar_unlocked();
            if (c == '\n') {
                if (!wordAdded) {
                    text.push_back(temp);
                    temp.second.clear();
                    wordAdded = true;
                }
                temp.first.second++;
                temp.first.first = 1;
            } else if (c == ' ' || c == '\t' || c == EOF) {
                // If there are multiple spaces in the text, we don't count them
                if (wordAdded)
                    continue;

                text.push_back(temp);
                temp.second.clear();
                temp.first.first++;
                wordAdded = true;
            } else {
                // Deletes unnecessary zeros in the number
                if (temp.second.front() == '0')
                    temp.second.erase(temp.second.begin());

                temp.second.push_back(c);
                wordAdded = false;
            }
        }

        // There are no possible matches if
        if (text.size() < pat.size())
            return;

        // KMP begins
        while (p < n && pat[p] == text[t].second ) { // We are checking if pattern suits or not
            ++p;
            ++t;
        }
        if (p == n) { // We found an entrance of pattern
            std::cout << text[0].first.second << ", " << text[0].first.first << std::endl;
        }
        if (p == 0) { // No matches at all
            ++t;
        }
        p = f[p];

        text.erase(text.begin(), text.begin() + t - p);
        t = p;

    } while (c != EOF);
}
