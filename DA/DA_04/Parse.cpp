#include "Parse.h"

std::vector<std::string> PatternParse() {
    char c;
    std::string buf;
    std::vector<std::string> pattern;

    while (true) {
        c = getchar_unlocked();
        if (c == ' ') {
            if (!buf.empty()) {
                pattern.push_back(buf);
            }
            buf.clear();
        }
        else if (c == '\n' || c == EOF) {
            if (!buf.empty()) {
                pattern.push_back(buf);
            }
            break;
        }
        else {
            buf.push_back(c);
        }
    }

    return pattern;
}