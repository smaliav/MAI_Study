#include <iostream>
#include <cstdlib>
#include "vector.h"
#include "struct.h"
#include "sort.h"

int main(){
    unsigned long long key, maxKey = 0, value;
    
    TVector *input = new TVector();
    TVector *output = new TVector();

    input->CreateVector();
    output->CreateVector();

    while(std::cin >> key >> value){
        if(key > maxKey) {
            maxKey = key;
        }
        KV cell(key, value);
        input->AddItem(cell);
    }

    input->CopyVector(input, output);
    
    RadixSort(input, maxKey, output);
    output->PrintVector();

    input->DeleteVector();
    output->DeleteVector();

    delete input;
    delete output;

    return 0;
}
