//
// Created by Pedro Tôrres on 19/10/2018.
//

#include <climits>
#include <vector>

#include "wu_manber.h"

pmt::wu_manber::wu_manber(std::list<std::string> &patterns, size_t edit_distance) : shift_or(patterns), e(edit_distance) {}

std::list<size_t> pmt::wu_manber::find(std::string &text) {
    std::list<size_t> occurrences;

    auto it0 = patterns.begin();
    auto it1 = cms.begin();
    while (it0 != patterns.end()) {
        auto &pattern = *it0++;
        auto &cm = *it1++;

        size_t m = pattern.length();

        if (text.length() < m)
            continue;

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
    }

    return occurrences;
}

bool pmt::wu_manber::exists(std::string &text) {
    auto it0 = patterns.begin();
    auto it1 = cms.begin();
    while (it0 != patterns.end()) {
        auto &pattern = *it0++;
        auto &cm = *it1++;

        size_t m = pattern.length();

        if (text.length() < m)
            continue;

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
    }

    return false;
}
