#include "TPatriciaTrieNode.h"

TPatriciaTrieNode::TPatriciaTrieNode(): id(0), key(nullptr), value(0), skip(0) {
    links[0] = this;
    links[1] = this;

}
TPatriciaTrieNode::TPatriciaTrieNode(TKey* k, TPatriciaData v, int sk): id(0), key(k), value(v), skip(sk) {
    links[0] = this;
    links[1] = this;
}

TPatriciaData TPatriciaTrieNode::GetValue() {
    return this->value;
}

void TPatriciaTrieNode::Init(TKey* k, TPatriciaData v, int sk, TPatriciaTrieNode* left, TPatriciaTrieNode* rigth) {
    id = 0;
    key = k;
    value = v;
    skip = sk;
    links[0] = left;
    links[1] = rigth;
}

TPatriciaTrieNode::~TPatriciaTrieNode() {
    if (this->key != nullptr)
        delete[] this->key;
}