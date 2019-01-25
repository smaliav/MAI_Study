//#include <iostream> //FOR DEBUG PRINT
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <cmath>

int GetRank(TVector *input, int i, int currentRank) {
    return (input->array[i].mKey / (unsigned long long)pow(100, currentRank)) % 100;
}

void CountingSort(TVector *input, int currentRank, TVector *output) {
    
    int maxKey = 0;

//*DEBUG*/std::cout << "INPUT:" << std::endl;
    for(int i = 0; i < input->size; i++) { //ОПРЕДЕЛЯЕМ САМЫЙ БОЛЬШОЙ КЛЮЧ
        int currentDigit = GetRank(input, i, currentRank);
        if(currentDigit > maxKey){
            maxKey = currentDigit;
        }
//*/DEBUG*/std::cout << currentDigit << " ";
    }
//*DEBUG*/std::cout << "\n";

    int *tmp = new int[maxKey + 1]; //СОЗДАЕМ МАССИВ ДЛЯ ПОСЧЕТА СЧИТЫВАЕМЫХ ЧИСЕЛ

//*DEBUG*/std::cout << "TMP:" << std::endl;
    for(int i = 0; i < maxKey + 1; i++) { //ОБНУЛЯЕМ МАССИВ ДЛЯ СЧИТЫВАЕМЫХ ЧИСЕЛ
        tmp[i] = 0;
//*DEBUG*/std::cout << tmp[i] << " ";
    }
//*DEBUG*/std::cout << "\n";

    for(int i = 0; i < input->size; i++) { //ИТЕРАТИВНО ДОБАВЛЯЕМ ЕДИНИЦУ В ЯЧЕЙКУ ВСТРЕЧЕННОГО ЧИСЛА
        ++tmp[GetRank(input, i, currentRank)];
    }

//*DEBUG*/std::cout << "TMP COUNTED:" << std::endl;
//*DEBUG*/for(int i = 0; i < maxKey + 1; i++) {
//*DEBUG*/   std::cout << tmp[i] << " ";
//*DEBUG*/}
//*DEBUG*/std::cout << "\n";

//*DEBUG*/std::cout << "TMP LEFT PLUS RIGHT:" << std::endl;
//*DEBUG*/std::cout << tmp[0] << " ";
    for(int i = 1; i < maxKey + 1; i++) { //К ПРАВОВОМУ ЭЛЕМЕНТУ ДОБАВЛЯЕМ ЛЕВЫЙ
        tmp[i] += tmp[i - 1]; 
//*DEBUG*/std::cout << tmp[i] << " ";
    }
//*DEBUG*/std::cout << "\n";

    for(int i = input->size - 1; i >= 0; i--) { //СОРТИРУЕМ В РЕЗУЛЬТИРУЮЩИЙ ВЕКТОР
        output->array[tmp[GetRank(input, i, currentRank)] - 1] = input->array[i];
        tmp[GetRank(input, i, currentRank)]--;
    }
//*DEBUG*/std::cout << "\nOUTPUT:" << std::endl;
//*DEBUG*/output->PrintVector();
//*DEBUG*/std::cout << "\n";

    input->ClearVector();

    output->CopyVector(output, input);

    delete [] tmp;
}

void RadixSort(TVector *input, unsigned long long maxKey, TVector *output) {
    int maxRank = 0;

    while(maxKey != 0) { //Определяем количество разрядов максимального ключа
        maxKey /= 100; // WAS 10
        maxRank++;
    }

    for(int currentRank = 0; currentRank < maxRank; currentRank++) {
        CountingSort(input, currentRank, output);
    }
}