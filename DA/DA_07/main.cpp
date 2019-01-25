#include <iostream>
#include <limits>

int main() {
    int n;          // Initial number
    int *values;    // Array of values
    int *ops;       // Array of operations (1 - "-1", 2 - "/2", 3 - "/3")

    std::cin >> n;

    values = new int [n];
    ops = new int [n];

    for (int i = 0; i < n; ++i) {
        values[i] = 0;
        ops[i] = 0;
    }

    // Main algorithm
    for (int i = 2; i <= n; ++i) {
        int div3 = std::numeric_limits<int>::max();
        int div2 = std::numeric_limits<int>::max();
        int m1;

        if (i % 3 == 0) {
            div3 = i + values[i / 3 - 1];
        }
        if (i % 2 == 0) {
            div2 = i + values[i / 2 - 1];
        }
        m1 = i + values[i - 2];

        if (div3 <= div2 && div3 <= m1) {
            values[i - 1] = div3;
            ops[i - 1] = 3;
        }
        else if (div2 <= div3 && div2 <= m1) {
            values[i - 1] = div2;
            ops[i - 1] = 2;
        }
        else {
            values[i - 1] = m1;
            ops[i - 1] = 1;
        }
    }

    std::cout << values[n - 1] << std::endl;

    for (int i = n - 1; i != 0;) {
        if (ops[i] == 3) {
            std::cout << "/3";
            i /= 3;
        }
        else if (ops[i] == 2) {
            std::cout << "/2";
            i /= 2;
        }
        else {
            std::cout << "-1";
            --i;
        }

        if (i != 0) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;

    delete [] values;
    delete [] ops;

    return 0;
}