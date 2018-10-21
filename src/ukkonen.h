//
// Created by Pedro Tôrres on 21/10/2018.
//

#ifndef PMT_UKKONEN_H
#define PMT_UKKONEN_H


#include <unordered_set>

#include "aho_corasick.h"

template <typename T>
struct std::hash<std::vector<T>> {
    size_t operator ()(const std::vector<T> &v) const {
        return std::_Hash_impl::hash(v.data(), v.size() * sizeof(T));
    }
};

class ukkonen : public string_searching_algorithm {
protected:
    const size_t e;
    std::unordered_set<size_t> tree;
    std::unordered_map<std::pair<size_t, char>, size_t> delta;
    static void init_fsm(std::unordered_set<size_t> &tree, std::unordered_map<std::pair<size_t, char>, size_t> &delta, std::string &pattern, size_t &e);

public:
    explicit ukkonen(std::string &pattern, size_t edit_distance);
    std::vector<size_t> find(std::string &text) override;
    bool exists(std::string &text) override;
};


#endif //PMT_UKKONEN_H
