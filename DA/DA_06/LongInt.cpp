#include "LongInt.h"

LongInt::LongInt() {}

LongInt::LongInt(size_t n) {
    if (n < BASE) {
        this->data.push_back(n);
    }
    else {
        while (n) {
            this->data.push_back(n % BASE);
            n /= BASE;
        }
    }
}

LongInt::LongInt(const std::string &str) {
    std::string text = str;

    for (int i = text.size() - 1; i >= 0; i -= R) {
        std::string num;
        for (int j = (i - R  + 1 > 0) ? i - R + 1: 0; j <= i; ++j) {
            if (num[0] == '0') {
                num = text[j];
                continue;
            }
            else {
                num += text[j];
            }
        }
        data.push_back(std::stoi(num));
    }

    DeleteZeros();
}

LongInt::~LongInt() {}

std::ostream& operator<<(std::ostream &stream, const LongInt &num) {
    if (num.Size() == 0) {
        return stream;
    }

    stream << num.data[num.Size() - 1];
    for (int i = num.Size() - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(R) << num.data[i];
    }

    return stream;
}

LongInt LongInt::operator+(const LongInt &other) {
    int k = 0;
    int r = 0;
    LongInt res;
    size_t n = std::max(this->Size(), other.Size());

    for (int i = 0; i < n; ++i) {
        if (this->Size() <= i) {
            k = other.data[i];
        }
        else if (other.Size() <= i) {
            k = this->data[i];
        }
        else {
            k = this->data[i] + other.data[i];
        }

        k += r;
        res.data.push_back(k % BASE);
        r = k / BASE;
    }

    if (r != 0) {
        res.data.push_back(r);
    }

    return res;
}

LongInt LongInt::operator-(const LongInt &other) {
    int k = 0;
    int r = 0;
    LongInt result;
    size_t n = std::max(this->Size(), other.Size());

    for (int i = 0; i < n; ++i) {
        int res = 0;

        if (other.Size() <= i) {
            res = this->data[i] + k;
        }
        else {
            res = this->data[i] - other.data[i] + k;
        }

        k = 0;
        if (res < 0) {
            res += BASE;
            k = -1;
        }
        r = res % BASE;

        result.data.push_back(r);
    }

    result.DeleteZeros();
    return result;
}

LongInt LongInt::operator*(const LongInt &other) const {
    size_t n = this->Size() * other.Size();
    LongInt result;
    result.Resize(n + 1);

    int k = 0;
    int r = 0;

    for (int i = 0; i < this->Size(); ++i) {
        for (int j = 0; j < other.Size(); ++j) {
            k = other.data[j] * this->data[i] + result.data[i + j];
            r = k / BASE;
            result.data[i + j + 1] += r;
            result.data[i + j] = k % BASE;
        }
    }

    result.DeleteZeros();
    return result;
}

LongInt LongInt::operator/(const LongInt &other) {
    LongInt result, cv("0");
    result.data.resize(this->data.size());

    for (int i = (int)this->data.size() - 1; i >= 0; --i) {
        cv.data.insert(cv.data.begin(), this->data[i]);
        if (!cv.data.back()) {
            cv.data.pop_back();
        }
        int x = 0, l = 0, r = BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            LongInt cur = other * LongInt(m);
            if (cur <= cv) {
                x = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        result.data[i] = x;
        cv = cv - other * LongInt(x);
    }

    result.DeleteZeros();
    return result;
}

bool LongInt::operator<(const LongInt &other) {
    if (this->Size() != other.Size()) {
        return this->Size() < other.Size();
    }

    for (int i = other.Size() - 1; i >= 0; --i) {
        if (this->data[i] != other.data[i]) {
            return this->data[i] < other.data[i];
        }
    }

    return false;
}

bool LongInt::operator<=(const LongInt &other) {
    return (*this < other) || (*this == other);

    /*
    if (this->Size() != other.Size()) {
        return this->Size() < other.Size();
    }

    for (int i = other.Size() - 1; i >= 0; --i) {
        if (this->data[i] != other.data[i]) {
            return this->data[i] <= other.data[i];
        }
    }

    return true;
    */
}

bool LongInt::operator>(const LongInt &other) {
    if (this->Size() != other.Size()) {
        return this->Size() > other.Size();
    }

    for (int i = other.Size() - 1; i >= 0; --i) {
        if (this->data[i] != other.data[i]) {
            return this->data[i] > other.data[i];
        }
    }

    return false;
}

bool LongInt::operator==(const LongInt &other) {
    if (this->Size() != other.Size()) {
        return false;
    }

    for (int i = other.Size() - 1; i >= 0; --i) {
        if (this->data[i] != other.data[i]) {
            return false;
        }
    }

    return true;
}

bool LongInt::Empty() {
    return this->data.empty();
}

size_t LongInt::Size() const {
    return this->data.size();
}

void LongInt::DeleteZeros() {
    while (data.size() > 1 && data.back() == 0) {
        data.pop_back();
    }
}

LongInt LongInt::Pow(LongInt &num) {
    LongInt result("1");

    while (!(num == 0)) {
        if (num.data.front() % 2 != 0) {
            result = result * (*this);
        }
        *this = *this * (*this);
        num = num / 2;
    }

    return result;
}

void LongInt::Resize(const size_t n) {
    this->data.resize(n, 0);
}