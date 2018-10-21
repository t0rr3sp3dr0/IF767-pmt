//
// Created by Pedro Tôrres on 21/10/2018.
//

#ifndef PMT_UKKONEN_H
#define PMT_UKKONEN_H


#include <unordered_set>
#include <vector>

#include "aho_corasick.h"

namespace std {
    template<typename T>
    struct hash<vector<T>> {
        size_t operator()(const vector<T> &v) const {
#if defined(__GNUC__) && !defined(__clang__)
            return _Hash_impl::hash(v.data(), v.size() * sizeof(T));
#else
            size_t hash_code = 0;
            for (auto &e : v)
                hash_code ^= hash<T>()(e);
            return hash_code;
#endif
        }
    };
}

namespace pmt {
    class ukkonen : public string_searching_algorithm {
    protected:
        const size_t e;
        std::list<std::unordered_set<size_t>> trees;
        std::list<std::unordered_map<std::pair<size_t, char>, size_t>> deltas;
        static void init_fsm(std::unordered_set<size_t> &tree, std::unordered_map<std::pair<size_t, char>, size_t> &delta, std::string &pattern, size_t &e);

    public:
        explicit ukkonen(std::list<std::string> &patterns, size_t edit_distance);
        std::list<size_t> find(std::string &text) override;
        bool exists(std::string &text) override;
    };
}


#endif //PMT_UKKONEN_H
