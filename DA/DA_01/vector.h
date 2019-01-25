#ifndef VECTOR_H
#define VECTOR_H
#include "struct.h"

class TVector{
public:
    unsigned int size;
    unsigned int freespace;
    KV *array;

    TVector();

    void CreateVector();
    void DeleteVector();
    void ClearVector();
    void AddItem(KV item);
    void ResizeVector();
    void PrintVector();
    void CopyVector(TVector *input, TVector *output);

    ~TVector();
};

#endif