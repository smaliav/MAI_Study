#include <cstdlib>
#include <iostream>
#include "struct.h"
#include "vector.h"

const static int INCREASE = 2;

TVector::TVector() {}

void TVector::CreateVector() {
    size = 0;
    array = (KV *)malloc(INCREASE * sizeof(KV));
    freespace = INCREASE;
}

void TVector::DeleteVector() {
    free(array);
    array = NULL;
    size = 0; //ПОД ВОПРОСОМ
    freespace = 0; //ПОД ВОПРОСОМ
}

void TVector::ClearVector() {
    free(array);
    this->CreateVector();
}

void TVector::AddItem(KV item) {
    if(!freespace)
        this->ResizeVector();
    array[size].mKey = item.mKey;
    array[size].mValue = item.mValue;
    size++;
    freespace--;
}

void TVector::ResizeVector() {
    array = (KV *)realloc(array, INCREASE * sizeof(KV) * size);
    freespace = size;
}

void TVector::PrintVector() {
    int i;
    for(i = 0; i < size; i++){
        std::cout << array[i].mKey << "\t" << array[i].mValue << std::endl; //printf("%s\t%s\n", array[i].mKey, array[i].mValue);
    }
}

void TVector::CopyVector(TVector *input, TVector *output) {
    int i;
    for(i = 0; i < input->size; i++){
        KV cell(input->array[i].mKey, input->array[i].mValue);
        output->AddItem(cell);
    }
}

TVector::~TVector() {}