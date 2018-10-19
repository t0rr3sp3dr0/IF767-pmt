//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_SHIFT_OR_H
#define PMT_SHIFT_OR_H


#include <bitset>

#include "string_searching_algorithm.h"

using dynamic_bitset = std::bitset<32>;

class shift_or : public string_searching_algorithm {
protected:
    std::vector<dynamic_bitset> cm;
    static void init_char_mask(std::vector<dynamic_bitset> &v, std::string &pattern);

public:
    explicit shift_or(std::string &pattern);
    std::vector<size_t> find(std::string &text) override;
    bool exists(std::string &text) override;
};


#endif //PMT_SHIFT_OR_H
