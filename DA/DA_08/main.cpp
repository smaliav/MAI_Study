#include <iostream>

void PrintArray(size_t *array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << array[i] << std::endl;
    }
}

int main() {
    size_t N;       // Power
    size_t p;       // Initial value
    uint32_t M;     // Total money
    size_t *vals;   // All values
    size_t *used;   // Used values

    std::cin >> N >> p >> M;

    vals = new size_t [N];
    used = new size_t [N];

    for (size_t i = 0, cur = 1; i < N; ++i) {
        vals[i] = cur;
        cur *= p;
    }

    // Main algorithm
    while (M) {
        static size_t curN = N - 1;
        static size_t count = 0;

        count = M / vals[curN];

        if (count == 0) {
            curN -= 1;
        }
        else {
            M -= vals[curN] * count;
            used[curN] = count;
            curN -= 1;
        }
    }

    PrintArray(used, N);

    delete [] vals;
    delete [] used;

    return 0;
}
