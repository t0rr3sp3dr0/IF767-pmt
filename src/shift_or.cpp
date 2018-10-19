//
// Created by Pedro Tôrres on 19/10/2018.
//

#include <climits>

#include "shift_or.h"

inline void shift_or::init_char_mask(std::vector<dynamic_bitset> &v, std::string &pattern) {
    dynamic_bitset pos_mask = -2;
    for (char &c : pattern) {
        v[c] &= pos_mask;
        pos_mask <<= 1;
        pos_mask |= 0x1;
    }
}

shift_or::shift_or(std::string &pattern) : string_searching_algorithm(pattern) {
    std::vector<dynamic_bitset> cm(UCHAR_MAX, -1);
    init_char_mask(cm, pattern);
    this->cm = cm;
}

std::vector<size_t> shift_or::find(std::string &text) {
    size_t m = pattern.length();

    std::vector<size_t> occurrences;

    dynamic_bitset s = -1;
    for (int i = 0; i < text.length(); ++i) {
        s = (s << 1) | cm[static_cast<unsigned char>(text[i])];

        if (!s[m - 1])
            occurrences.emplace_back(i - m + 1);
    }

    return occurrences;
}

bool shift_or::exists(std::string &text) {
    size_t m = pattern.length();

    dynamic_bitset s = -1;
    for (char &c : text) {
        s = (s << 1) | cm[static_cast<unsigned char>(c)];

        if (!s[m - 1])
            return true;
    }

    return false;
}
