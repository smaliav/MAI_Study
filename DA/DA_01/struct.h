#ifndef STRUCT_H
#define STRUCT_H

class KV{
public:
    unsigned long long mKey;
    unsigned long long mValue;

    KV() {};
    KV(unsigned long long key, unsigned long long value): mKey(key), mValue(value) {}
};

#endif