#include <fstream>
#include <iostream>
#include <cstring>
#include "TPatriciaTrie.h"

void Lowercase(char *str) {
    int len = std::strlen(str);
    for (int i = 0; i < len; ++i)
        str[i] = std::tolower(str[i]);
}

int main(int argc, char** argv) {
    // Файлы
    std::ofstream fout;
    std::ifstream fin;

    char input[MAX_SIZE];
    TPatriciaData value;
    TPatriciaTrieNode* node;

    TPatriciaTrie* trie = new TPatriciaTrie();
    TPatriciaTrie* trie2 = nullptr; // Нужно для сохранения
    while ((std::cin >> input)) {

        // Ошибка при чтении входного файла
        if (!std::cin) {
            std::cout << "ERROR: input option can not be read " << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        // Добавление в дерево
        if (!std::strcmp(input, "+")) {
            std::cin >> input;
            Lowercase(input);
            std::cin >> value;
            if (!std::cin) {
                std::cout << "ERROR: input value can not be read " << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
            std::cout << (trie->Insert(input, value) ? "OK" : "Exist");
            std::cout << std::endl;
        }
        // Удаление из дерева
        else if (!std::strcmp(input, "-")) {
            std::cin >> input;
            Lowercase(input);
            std::cout << (trie->Delete(input) ? "OK" : "NoSuchWord");
            std::cout << std::endl;
        }
        // Сохранение/Загрузка
        else if (!std::strcmp(input, "!")) {
            std::cin >> input;
            if (!std::strcmp(input, "Save")) {
                std::cin >> input;
                fout.open(input, std::ios::out | std::ios::binary | std::ios::trunc);
                if (!fout.is_open()) {
                    std::cout << "ERROR: Couldn't create file" << std::endl;
                    continue;
                }

                if (trie->Save(&fout))
                    std::cout << "OK";
                else
                    std::cout << "ERROR: Could not create dictionary";

                std::cout << std::endl;
                fout.close();

            }
            else if (!std::strcmp(input, "Load")) {
                std::cin >> input;
                fin.open(input, std::ios::in | std::ios::binary);
                if (!fin.is_open()) {
                    std::cout << "ERROR: Couldn't open file" << std::endl;
                    continue;
                }
                trie2 = new TPatriciaTrie();
                if (trie2->Load(&fin)) {
                    std::cout << "OK" << std::endl;
                    delete trie;
                    trie = trie2;
                }
                else {
                    std::cout << "ERROR: Wrong dictionary format" << std::endl;
                    delete trie2;
                }
                fin.close();
            }
            else {
                std::cout << "ERROR: input option can not be read" << std::endl;
                continue;
            }
        }
        // Поиск в дереве
        else {
            Lowercase(input);
            node = trie->Find(input);
            if (!node)
                std::cout << "NoSuchWord";
            else
                std::cout << "OK: " << node->GetValue();
            std::cout << std::endl;
        }
    }
    delete trie;
    return 0;
}