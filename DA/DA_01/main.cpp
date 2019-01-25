#include <iostream>
#include <cstdlib>
#include "vector.h"
#include "struct.h"
#include "sort.h"

int main(){
    unsigned long long key, maxKey = 0, value;
    
    TVector *input = new TVector(); //EDIT, PUT THIS IN THE CONSTRUCTOR
    TVector *output = new TVector(); //EDIT, PUT THIS IN THE CONSTRUCTOR

    input->CreateVector(); //EDIT, PUT THIS FUNCTION IN THE CONSTRUCTOR
    output->CreateVector(); //EDIT, PUT THIS FUNCTION IN THE CONSTRUCTOR

    while(std::cin >> key >> value){
        if(key > maxKey) {
            maxKey = key;
        }
        KV cell(key, value);
        input->AddItem(cell);
    }

    input->CopyVector(input, output); //EDIT, NOT NECCESSARY ACTIONS INCLUDED
    
    RadixSort(input, maxKey, output);
    output->PrintVector();

    input->DeleteVector();
    output->DeleteVector();

    delete input;
    delete output;

    return 0;
}