#ifndef TPATRICIATRIENODE_H
#define TPATRICIATRIENODE_H

#include <iostream>
#include <cstring>
#include <fstream> // Нужно ли это?

const int MAX_SIZE = 257;
typedef unsigned long long TPatriciaData;
typedef char TKey;

class TPatriciaTrieNode {
public:
    TPatriciaTrieNode();
    TPatriciaTrieNode(TKey*, TPatriciaData, int sk);

    TPatriciaData GetValue();

    virtual ~TPatriciaTrieNode();

private:
    friend class TPatriciaTrie;

    int id; // Уникальный номер каждого узла
            // Используется для сериализации
            // Просчитывается в функции Index

    TKey* key;
    TPatriciaData value;
    int skip;
    TPatriciaTrieNode* links[2]; // Указатели на поддеревья (0 - левое, 1 - правое)

    void Init(TKey*, TPatriciaData, int sk, TPatriciaTrieNode* left, TPatriciaTrieNode* right);
};

#endif /* TPATRICIATRIENODE_H */