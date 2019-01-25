#ifndef LONGINT_H
#define LONGINT_H

#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstdlib>

const int R = 4;
const int BASE = pow(10, R);

class LongInt {
public:
    LongInt();
    LongInt(size_t n);
    LongInt(const std::string &str);
    ~LongInt();

    friend std::ostream &operator<<(std::ostream &stream, const LongInt &num);

    LongInt operator+(const LongInt &other);
    LongInt operator-(const LongInt &other);
    LongInt operator*(const LongInt &other) const;
    LongInt operator/(const LongInt &other);

    bool operator<(const LongInt &other);
    bool operator>(const LongInt &other);
    bool operator==(const LongInt &other);
    bool operator<=(const LongInt &other);

    bool Empty();
    size_t Size() const;
    LongInt Pow(LongInt &num);

private:
    void Resize(const size_t n);
    void DeleteZeros();

    std::vector<uint32_t> data;
};

#endif /* LONGINT_H */
