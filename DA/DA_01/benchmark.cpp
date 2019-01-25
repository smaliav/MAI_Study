#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

int GetRank(std::vector <std::pair <unsigned long long, unsigned long long> > &input, int i, int &currentRank) {
    return input[i].first / (unsigned long long)pow(10000, currentRank) % 10000;
}

bool CheckOrder (const std::vector <std::pair <unsigned long long, unsigned long long> > &data) {
    for (size_t idx = 1; idx < data.size(); ++idx) {
        if (data[idx - 1].first > data[idx].first) {
            return false;
        }
    }
    return true;
}

bool PairComparer (const std::pair <unsigned long long, unsigned long long> &a, std::pair <unsigned long long, unsigned long long> &b) {
    return a.first < b.first;
}

void CountingSort (std::vector <std::pair <unsigned long long, unsigned long long> > &input, int &currentRank) {
    int size = input.size(); //ВОЗМОЖНО CAPACITY ВМЕСТО SIZE
    int max = 0;

    for (int i = 0; i < size; i++) {
        int currentDigit = GetRank(input, i, currentRank);
        if (currentDigit > max) {
            max = currentDigit;
        }
    }

    std::vector <std::pair <unsigned long long, unsigned long long> > res(size);
    int *countMass = new int[max + 1];
    
    for (int i = 0; i < max + 1; ++i) {
        countMass[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        countMass[GetRank(input, i, currentRank)]++; //countMass[input[i].first]++;
    }
    for (int i = 1; i <= max; ++i) {
        countMass[i] = countMass[i] + countMass[i - 1];
    }
    for (int i = size - 1; i >= 0; i--) {
        int tmp = countMass[GetRank(input, i, currentRank)] - 1; //(input)[i].first] - 1;
        res[tmp] = input[i];
        countMass[GetRank(input, i, currentRank)] = countMass[GetRank(input, i, currentRank)] - 1; //input[i].first] = countMass[input[i].first] - 1;
    }
    for (int i = 0; i < size; ++i) {
        input[i] = res[i];
    }
    delete[] countMass;
}

void RadixSort(std::vector <std::pair <unsigned long long, unsigned long long> > &input, unsigned long long &maxKey) {
    int maxRank = 0;

    while(maxKey != 0) {
        maxKey /= 10000;
        maxRank++;
    }

    for(int currentRank = 0; currentRank < maxRank; currentRank++) {
        CountingSort(input, currentRank);
    }
}

void StdSort (std::vector <std::pair <unsigned long long, unsigned long long> > &data) {
    std::sort(data.begin(), data.end(), PairComparer);
}

void RunStdSort (std::vector <std::pair <unsigned long long, unsigned long long> > &data) {
    clock_t start = clock();
    StdSort(data);
    clock_t end = clock();
    assert(CheckOrder(data) == true);
    double time = (double)(end - start);
    printf("\nStd SortTime = %lf\n",time/CLOCKS_PER_SEC);
}

void RunRadixSort(std::vector <std::pair <unsigned long long, unsigned long long> > &data, unsigned long long &maxKey) {
    clock_t start = clock();
    RadixSort(data, maxKey);
    clock_t end = clock();
    assert(CheckOrder(data) == true);
    double time = (double)(end - start);
    printf("\nRadix SortTime = %lf\n",time/CLOCKS_PER_SEC);
}

int main(int argc, const char *argv[]) {
    std::vector <std::pair <unsigned long long, unsigned long long> > data;
    std::pair <unsigned long long, unsigned long long> pair;
    unsigned long long key;
    unsigned long long maxKey = 0;
    unsigned long long value;
    
    while (scanf("%llu", &key) != EOF) {
        scanf("%llu", &value);
        pair.first = key;
        pair.second = value;

        if (key > maxKey) {
            maxKey = key;
        }

        data.push_back(pair);
    }

    std::vector <std::pair <unsigned long long, unsigned long long> > dataCopy(data);

    RunStdSort(data);
    RunRadixSort(dataCopy, maxKey);
    
    return 0;
}