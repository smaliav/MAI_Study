#include "TPatriciaTrie.h"

TPatriciaTrie::TPatriciaTrie(): size(0) {
    // Корень не будет проходить по дереву во время удаления //head will not moves around the trie during 'Delete'
    head = new TPatriciaTrieNode(nullptr, 0, -1);
}

TPatriciaTrie::~TPatriciaTrie() {
    DestructRecursive(head);
}

void TPatriciaTrie::DestructRecursive(TPatriciaTrieNode* node) {

    if (node->links[0]->skip > node->skip)
        DestructRecursive(node->links[0]);
    if (node->links[1]->skip > node->skip)
        DestructRecursive(node->links[1]);
    delete node;
}

TPatriciaTrieNode* TPatriciaTrie::Find(TKey* k) {

    if (this->IsEmpty())
        return nullptr;

    TPatriciaTrieNode* pref = head; // Прошлый проверенный узел (префикс)
    TPatriciaTrieNode* ref = head->links[0]; // Текущий проверяемый узел

    while (pref->skip < ref->skip) {
        pref = ref;
        ref = pref->links[BitGet(k, pref->skip)];
    }

    // Сравнивает найденый и искомый узел
    if (!KeyCompare(k, ref->key))
        return nullptr;

    return ref;
}

bool TPatriciaTrie::Insert(TKey* k, TPatriciaData d) {

    TPatriciaTrieNode* prev = head; // Предыдущий проверенный узел
    // Он находится до узла, который будет вставлен

    TPatriciaTrieNode* nxt = head->links[0]; // Текущий проверяемый узел
    // Он находится после узла, который будет вставлен

    while (prev->skip < nxt->skip) {
        prev = nxt;
        nxt = prev->links[BitGet(k, nxt->skip)];
    }

    // Проверяет существует ли уже ключ в дереве
    if (KeyCompare(k, nxt->key))
        return false;

    int bitPrefix = FirstDifferentBit(k, nxt->key);

    prev = head;
    nxt = head->links[0];
    while (prev->skip < nxt->skip && nxt->skip < bitPrefix) {
        prev = nxt;
        nxt = prev->links[BitGet(k, nxt->skip)];
    }
    // Мы нашли нужно место для вставки нового узла в дерево

    // Компактное представление памяти для ключей
    TKey* compactKey;
    try {
        compactKey = new TKey[ByteLen(k) + 1];
    } catch (const std::bad_alloc &) {
        std::cout << "ERROR: not enough memory" << std::endl;
        return false;
    }
    std::strcpy(compactKey, k);

    // Интеграция нового узла в дерево
    TPatriciaTrieNode* newNode = new TPatriciaTrieNode(compactKey, d, bitPrefix);
    prev->links[BitGet(compactKey, prev->skip)] = newNode;
    newNode->links[BitGet(compactKey, bitPrefix)] = newNode;
    newNode->links[1 - BitGet(compactKey, bitPrefix)] = nxt;
    this->size++;

    return true;
}

bool TPatriciaTrie::Delete(TKey* k) {

    TPatriciaTrieNode *grandParent = nullptr; // Узел, предшедствующий родительскому
    TPatriciaTrieNode *parent = head;         // Родитель узла, который нужно удалить
    TPatriciaTrieNode *del = head->links[0];  // Узел, который нам нужно удалить

    while (parent->skip < del->skip) {
        grandParent = parent;
        parent = del;
        del = del->links[BitGet(k, del->skip)];
    }

    // Проверяет, соответсвует ли найденный ключ искомому
    if (!KeyCompare(k, del->key))
        return false;

    // Копирует ключ и значение 'parent' в 'del'
    if (del != parent) {
        SetKey(del, parent);
        del->value = parent->value;
    }

    // Проверяет является ли p листом
    if (parent->links[0]->skip > parent->skip || parent->links[1]->skip > parent->skip) {
        // 'parent' не лист, поэтому хотя бы один сын есть
        if (parent != del) {
            // Если ссылка вверх на узел ледит глубже, чем ближайший сын
            // То нужно найти точный узел с этой ссылкой

            TPatriciaTrieNode* parentOfParent = parent;
            TPatriciaTrieNode* tmp = parent->links[BitGet(parent->key, parent->skip)];
            TKey* key = parent->key;

            // Точный узел с ссылкой наверх будет теперь будет родителем 'del'
            while (parentOfParent->skip < tmp->skip) {
                parentOfParent = tmp;
                tmp = parentOfParent->links[BitGet(key, parentOfParent->skip)];
            }

            if (!KeyCompare(key, tmp->key)) {
                std::cout << "ERROR: logical error during Delete (incorrect generated trie?)";
                std::cout << std::endl;
                return false;
            }

            parentOfParent->links[BitGet(key, parentOfParent->skip)] = del;
        }

        // Переподключить 'grandParent', чтобы он показывал на реального сына 'parent'
        if (grandParent != parent)
            grandParent->links[BitGet(k, grandParent->skip)] = parent->links[1 - BitGet(k, parent->skip)];
    }
    else {
        // Если это лист, то хотя бы одна ссылка ведет в себя и все ведут вверх

        // Переподключить 'grandParent'
        if (grandParent != parent) {
            /*grandParent->links[BitGet(k, grandParent->skip)] =
                    (parent->links[0] == parent) ?
                    (parent->links[1] == parent) ?
                    grandParent : parent->links[1] : parent->links[0];*/
            if (parent->links[0] == parent) {
                if (parent->links[1] == parent)
                    grandParent->links[BitGet(k, grandParent->skip)] = grandParent;
                else
                    grandParent->links[BitGet(k, grandParent->skip)] = parent->links[1];
            }
            else
                grandParent->links[BitGet(k, grandParent->skip)] = parent->links[0];
        }
    }

    this->size--;
    delete parent;
    return true;
}

void TPatriciaTrie::SwapKeys(TPatriciaTrieNode* nodea, TPatriciaTrieNode* nodeb) {
    TKey* tmp = nodea->key;
    TPatriciaData dat = nodea->value;
    nodea->key = nodeb->key;
    nodea->value = nodeb->value;
    nodeb->key = tmp;
    nodeb->value = dat;
}

void TPatriciaTrie::SetKey(TPatriciaTrieNode* to, TPatriciaTrieNode* from) {
    if (from->key == nullptr)
        to->key = nullptr;
    else
        std::strcpy(to->key, from->key);
}

bool TPatriciaTrie::IsEmpty() {
    // Дерево пустое, если все ссылку из корня ведут в корень
    return (head->links[0] == head) && (head->links[1] == head);
}

int TPatriciaTrie::BitLen(TKey* k) {
    if (k == nullptr)
        return 0;
    return std::strlen(k) * 8;
}

int TPatriciaTrie::ByteLen(TKey* k) {
    if (k == nullptr)
        return 0;
    return std::strlen(k);
}

int TPatriciaTrie::BitGet(TKey* k, int bit) {
    if (bit < 0)
        bit = 0;

    int count = 7 - (bit & 7);

    return ((k[bit >> 3] >> count) & 1U);
}

bool TPatriciaTrie::KeyCompare(TKey* key1, TKey* key2) {
    if (key1 == key2) // Ключи совпадают
        return true;

    int len = BitLen(key1);
    if (len != BitLen(key2))  // Ключи разной длинны и тогда не точно не совпадают
        return false;

    if (FirstDifferentBit(key1, key2) != len)
        return false;

    return true;
}

int TPatriciaTrie::FirstDifferentBit(TKey* key1, TKey* key2) {
    if (!key1)
        return 0;
    if (!key2)
        return 0;

    size_t differ = 0;
    size_t len1 = ByteLen(key1);
    size_t len2 = ByteLen(key2);
    size_t minlen = len2 > len1 ? len1 : len2;
    size_t maxlen = len2 < len1 ? len1 : len2;

    // Находим первый различный символ
    while ((key1[differ] == key2[differ]) && differ < minlen)
        differ++;
    differ *= 8;
    maxlen *= 8;

    while (BitGet(key2, differ) == BitGet(key1, differ) && differ < maxlen)
        // Находим первый различный бит
        differ++;

    return differ;
}

bool TPatriciaTrie::Save(std::ofstream* file) {
    file->write((char*) &(this->size), sizeof(int));
    int index = 0;
    TPatriciaTrieNode** nodes = new TPatriciaTrieNode*[this->size + 1];
    TPatriciaTrieNode* node;
    Index(head, nodes, &index);
    for (int i = 0; i < (size + 1); ++i) {
        node = nodes[i];
        file->write((char*) &(node->value), sizeof(TPatriciaData));
        file->write((char*) &(node->skip), sizeof(int));
        int len = ByteLen(node->key);
        file->write((char*) &(len), sizeof(int));
        file->write(node->key, len);
        file->write((char*) &(node->links[0]->id), sizeof(int));
        file->write((char*) &(node->links[1]->id), sizeof(int));
    }
    delete[] nodes;

    if (file->fail())
        return false;

    return true;
}

void TPatriciaTrie::Index(TPatriciaTrieNode* node, TPatriciaTrieNode** nodes, int* index) {
    node->id = *index;
    nodes[*index] = node;
    (*index)++;

    if (node->links[0]->skip > node->skip)
        Index(node->links[0], nodes, index);
    if (node->links[1]->skip > node->skip)
        Index(node->links[1], nodes, index);
}

bool TPatriciaTrie::Load(std::ifstream* file) {
    int size;
    TPatriciaTrieNode** nodes;

    // Считываем количество узлов в дереве
    file->read((char*) &size, sizeof(int));
    this->size = size;
    if (!size)
        return true;

    try {
        nodes = new TPatriciaTrieNode*[size + 1];
    } catch (const std::bad_alloc &) {
        return false;
    }
    nodes[0] = this->head;

    // Делаем узлы
    int var;
    try {
        for (var = 1; var < (size + 1); ++var)
            nodes[var] = new TPatriciaTrieNode();
    } catch (const std::bad_alloc &) {
        std::cout << "ERROR: not enough memory" << std::endl;
        for (int i = 0; i < var; ++i)
            delete nodes[i];
        delete[] nodes;
        return false;
    }

    TPatriciaData value;
    int skip;
    int len;
    TKey* key;
    int indLeft, indRight; // Дети
    try {
        for (int i = 0; i < (size + 1); ++i) {
            file->read((char*) &(value), sizeof(TPatriciaData));
            file->read((char*) &(skip), sizeof(int));
            file->read((char*) &(len), sizeof(int));
            key = new char[len + 1];
            key[len] = 0;
            file->read(key, len);
            file->read((char*) &(indLeft), sizeof(int));
            file->read((char*) &(indRight), sizeof(int));
            nodes[i]->Init(key, value, skip, nodes[indLeft], nodes[indRight]);
        }
    }
    catch (const std::bad_alloc &) {
        std::cout << "ERROR: not enough memory" << std::endl;
        for (int i = 0; i < this->size; i++)
            delete nodes[i];
        delete[] nodes;
        return false;
    }

    file->peek();
    if (file->fail() || !file->eof()) {
        // Неверный формат
        for (int i = 0; i < this->size; i++)
            delete nodes[i];
        delete[] nodes;
        return false;
    }

    delete[] nodes;

    return true;
}