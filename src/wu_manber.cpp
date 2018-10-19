//
// Created by Pedro Tôrres on 19/10/2018.
//

#include <climits>

#include "wu_manber.h"

wu_manber::wu_manber(std::string &pattern, size_t edit_distance) : shift_or(pattern), e(edit_distance) {}

std::vector<size_t> wu_manber::find(std::string &text) {
    size_t m = pattern.length();

    std::vector<size_t> occurrences;

    std::vector<dynamic_bitset> s(e + 1, -1);
    for (size_t i = 0; i < text.length(); ++i) {
        s[0] = (s[0] << 1) | cm[static_cast<unsigned char>(text[i])];

        dynamic_bitset prev = s[0];
        for (size_t j = 1; j <= e; ++j) {
            dynamic_bitset db = s[j];
            s[j] = ((s[j] << 1) | cm[static_cast<unsigned char>(text[i])]) & (s[j - 1] << 1) & (prev << 1) &
                   prev;
            prev = db;
        }

        if (!s[e][m - 1])
            occurrences.emplace_back(i);
    }

    return occurrences;
}

bool wu_manber::exists(std::string &text) {
    size_t m = pattern.length();

    std::vector<dynamic_bitset> s(e + 1, -1);
    for (char &c : text) {
        s[0] = (s[0] << 1) | cm[static_cast<unsigned char>(c)];

        dynamic_bitset prev = s[0];
        for (size_t i = 1; i <= e; ++i) {
            dynamic_bitset db = s[i];
            s[i] = ((s[i] << 1) | cm[static_cast<unsigned char>(c)]) & (s[i - 1] << 1) & (prev << 1) & prev;
            prev = db;
        }

        if (!s[e][m - 1])
            return true;
    }

    return false;
}
