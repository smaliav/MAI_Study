#ifndef TPATRICIATRIE_H
#define TPATRICIATRIE_H

#include <iostream>
#include <cstring>
#include <fstream>
#include "TPatriciaTrieNode.h"

class TPatriciaTrie {
public:
    TPatriciaTrie();

    bool Insert(TKey*, TPatriciaData); // Возвращает true, если вставка прошла успешно, false в противном случае
    TPatriciaTrieNode* Find(TKey*);
    bool Delete(TKey* k);
    bool IsEmpty();
    bool Save(std::ofstream*);
    bool Load(std::ifstream*);

    virtual ~TPatriciaTrie();

private:
    TPatriciaTrieNode* head;
    int size;

    static bool KeyCompare(TKey*, TKey*);
    static int BitLen(TKey*);
    static int ByteLen(TKey*);
    static int BitGet(TKey*, int);
    static int FirstDifferentBit(TKey*, TKey*);
    void SwapKeys(TPatriciaTrieNode* nodea, TPatriciaTrieNode* nodeb);
    void SetKey(TPatriciaTrieNode* nodea, TPatriciaTrieNode* nodeb);

    void DestructRecursive(TPatriciaTrieNode* n);
    void Index(TPatriciaTrieNode* node, TPatriciaTrieNode** nodes, int* depth);
};

#endif /* TPATRICIA_TRIE */