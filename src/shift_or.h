//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_SHIFT_OR_H
#define PMT_SHIFT_OR_H


#include <bitset>
#include <vector>

#include "string_searching_algorithm.h"

using dynamic_bitset = std::bitset<sizeof(size_t) * 8>;

namespace pmt {
    class shift_or : public string_searching_algorithm {
    protected:
        std::list<std::vector<dynamic_bitset>> cms;
        static void init_char_mask(std::vector<dynamic_bitset> &v, std::string &pattern);

    public:
        explicit shift_or(std::list<std::string> &patterns);
        std::list<size_t> find(std::string &text) override;
        bool exists(std::string &text) override;
    };
}


#endif //PMT_SHIFT_OR_H
