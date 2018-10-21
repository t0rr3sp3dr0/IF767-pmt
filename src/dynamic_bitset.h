#ifndef PMT_DYNAMIC_BITSET_H
#define PMT_DYNAMIC_BITSET_H


#include <bitset>
#include <vector>
#include <ostream>

class dynamic_bitset {
public:
    static constexpr size_t WORD = sizeof(size_t) * 8;

protected:
    const size_t capacity;
    std::vector<std::bitset<dynamic_bitset::WORD>> data;

public:
    explicit dynamic_bitset(size_t capacity);
    dynamic_bitset(size_t capacity, size_t i);
    dynamic_bitset &operator=(size_t i);
    dynamic_bitset &operator=(dynamic_bitset db);
    bool operator[](size_t i);
    void flip();
    void operator|=(size_t i);
    void operator|=(const dynamic_bitset &db);
    void operator&=(size_t i);
    void operator&=(const dynamic_bitset &db);
    void operator<<=(size_t i);
    void operator>>=(size_t i);
    dynamic_bitset operator~();
    dynamic_bitset operator|(size_t i);
    dynamic_bitset operator|(dynamic_bitset db);
    dynamic_bitset operator&(size_t i);
    dynamic_bitset operator&(dynamic_bitset db);
    dynamic_bitset operator<<(size_t i);
    dynamic_bitset operator>>(size_t i);
    friend std::ostream &operator<<(std::ostream &os, const dynamic_bitset &db);
};


#endif //PMT_DYNAMIC_BITSET_H
