//
// Created by Pedro Tôrres on 21/10/2018.
//

#include <stdexcept>

#include "dynamic_bitset.h"

dynamic_bitset::dynamic_bitset(size_t capacity) : capacity(capacity) {
    this->data.resize(1 + ((capacity - 1) / dynamic_bitset::WORD));
}

dynamic_bitset::dynamic_bitset(size_t capacity, size_t i) : dynamic_bitset(capacity) {
    *this = i;
}

dynamic_bitset &dynamic_bitset::operator=(size_t i) {
    this->data[0] = i;
    for (size_t j = 1; j < this->data.size(); ++j)
        this->data[j] = this->data[0][dynamic_bitset::WORD - 1] ? -1 : 0;
    return *this;
}

dynamic_bitset &dynamic_bitset::operator=(dynamic_bitset db) {
    if (db.capacity != this->capacity)
        throw std::runtime_error(std::to_string(db.capacity) + " != " + std::to_string(this->capacity));

    for (size_t i = 0; i < this->data.size(); ++i)
        this->data[i] = db.data[i];
    return *this;
}

bool dynamic_bitset::operator[](size_t i) {
    if (i >= this->capacity)
        throw std::out_of_range(std::to_string(i) + " >= " + std::to_string(this->capacity));

    return this->data[i / dynamic_bitset::WORD][i % dynamic_bitset::WORD];
}

void dynamic_bitset::flip() {
    for (auto &e : this->data)
        e.flip();
}

void dynamic_bitset::operator|=(size_t i) {
    this->data[0] |= i;
}

void dynamic_bitset::operator|=(const dynamic_bitset &db) {
    if (db.capacity != this->capacity)
        throw std::runtime_error(std::to_string(db.capacity) + " != " + std::to_string(this->capacity));

    for (size_t i = 0; i < this->data.size(); ++i)
        this->data[i] |= db.data[i];
}

void dynamic_bitset::operator&=(size_t i) {
    this->data[0] &= i;
}

void dynamic_bitset::operator&=(const dynamic_bitset &db) {
    if (db.capacity != this->capacity)
        throw std::runtime_error(std::to_string(db.capacity) + " != " + std::to_string(this->capacity));

    for (size_t i = 0; i < this->data.size(); ++i)
        this->data[i] &= db.data[i];
}

void dynamic_bitset::operator<<=(size_t i) {
    if (i != 1)
        throw std::runtime_error(std::to_string(i) + " != 1");

    bool carry_out = false;
    for (auto &e : this->data) {
        bool b = e[dynamic_bitset::WORD - 1];
        e <<= 1;
        e |= carry_out;
        carry_out = b;
    }
}

void dynamic_bitset::operator>>=(size_t i) {
    throw std::runtime_error("not implemented");
}

dynamic_bitset dynamic_bitset::operator~() {
    dynamic_bitset copy = *this;
    copy.flip();
    return copy;
}

dynamic_bitset dynamic_bitset::operator|(size_t i) {
    dynamic_bitset copy = *this;
    copy |= i;
    return copy;
}

dynamic_bitset dynamic_bitset::operator|(dynamic_bitset db) {
    dynamic_bitset copy = *this;
    copy |= db;
    return copy;
}

dynamic_bitset dynamic_bitset::operator&(size_t i) {
    dynamic_bitset copy = *this;
    copy &= i;
    return copy;
}

dynamic_bitset dynamic_bitset::operator&(dynamic_bitset db) {
    dynamic_bitset copy = *this;
    copy &= db;
    return copy;
}

dynamic_bitset dynamic_bitset::operator<<(size_t i) {
    dynamic_bitset copy = *this;
    copy <<= i;
    return copy;
}

dynamic_bitset dynamic_bitset::operator>>(size_t i) {
    dynamic_bitset copy = *this;
    copy >>= i;
    return copy;
}

std::ostream &operator<<(std::ostream &os, const dynamic_bitset &db) {
    bool b = false;
    for (auto &e : db.data) {
        if (b)
            os << ' ';
        else
            b = true;
        os << e;
    }
    return os;
}
