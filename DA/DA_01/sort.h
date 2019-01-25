#ifndef SORT_H
#define SORT_H
#include "struct.h"
#include "vector.h"

void CountingSort(TVector *input, /*unsigned long long maxKey*/ int rank, TVector *output);

void RadixSort(TVector *input, unsigned long long maxKey, TVector *output);

#endif