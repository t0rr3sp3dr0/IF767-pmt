#include <climits>

#include "shift_or.h"

inline void pmt::shift_or::init_char_mask(std::vector<dynamic_bitset> &v, std::string &pattern) {
    dynamic_bitset pos_mask = -2;
    for (char &c : pattern) {
        v[c] &= pos_mask;
        pos_mask <<= 1;
        pos_mask |= 0x1;
    }
}

pmt::shift_or::shift_or(std::list<std::string> &patterns) : string_searching_algorithm(patterns) {
    for (auto &pattern : patterns) {
        std::vector<dynamic_bitset> cm(UCHAR_MAX, -1);
        init_char_mask(cm, pattern);
        this->cms.emplace_back(cm);
    }
}

std::list<size_t> pmt::shift_or::find(std::string &text) {
    std::list<size_t> occurrences;

    auto it0 = patterns.begin();
    auto it1 = cms.begin();
    while (it0 != patterns.end()) {
        auto &pattern = *it0++;
        auto &cm = *it1++;

        size_t m = pattern.length();

        if (text.length() < m)
            continue;

        dynamic_bitset s = -1;
        for (int i = 0; i < text.length(); ++i) {
            s = (s << 1) | cm[static_cast<unsigned char>(text[i])];

            if (!s[m - 1])
                occurrences.emplace_back(i - m + 1);
        }
    }

    return occurrences;
}

bool pmt::shift_or::exists(std::string &text) {
    auto it0 = patterns.begin();
    auto it1 = cms.begin();
    while (it0 != patterns.end() && it1 != cms.end()) {
        auto &pattern = *it0++;
        auto &cm = *it1++;

        size_t m = pattern.length();

        if (text.length() < m)
            continue;

        dynamic_bitset s = -1;
        for (char &c : text) {
            s = (s << 1) | cm[static_cast<unsigned char>(c)];

            if (!s[m - 1])
                return true;
        }
    }

    return false;
}
