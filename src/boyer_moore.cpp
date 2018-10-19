//
// Created by Pedro Tôrres on 19/10/2018.
//

#include <climits>

#include "boyer_moore.h"

inline void boyer_moore::init_border(std::vector<size_t> &v, std::string &pattern) {
    size_t m = pattern.length();
    size_t c = m - 1;

    for (size_t i = 1, j = 0; i + j < m; i += std::max(j - v[j], static_cast<size_t>(1)), j = v[j])
        while (i + j < m && pattern[c - (i + j)] == pattern[c - j]) {
            ++j;
            v[i + j] = j;
        }
}

inline void boyer_moore::init_good_suffix(std::vector<size_t> &v, std::string &pattern) {
    size_t m = pattern.length();

    std::vector<size_t> b(pattern.length() + 1);
    boyer_moore::init_border(b, pattern);

    fill(v.begin(), v.end(), m - b[m]);
    for (size_t l = 1; l <= m; ++l) {
        size_t j = std::min(m - 1 - b[l], m);
        if (v[j] > l - b[l])
            v[j] = l - b[l];
    };
}

inline void boyer_moore::init_bad_char(std::vector<size_t> &v, std::string &pattern) {
    size_t i = 0;
    for (char &c : pattern)
        v[c] = i++;
}

boyer_moore::boyer_moore(std::string &pattern) : string_searching_algorithm(pattern) {
    std::vector<size_t> bc(UCHAR_MAX, static_cast<size_t>(-1));
    boyer_moore::init_bad_char(bc, pattern);
    this->bc = bc;

    std::vector<size_t> gs(pattern.length() + 1);
    boyer_moore::init_good_suffix(gs, pattern);
    this->gs = gs;
}

inline std::vector<size_t> boyer_moore::find(std::string &text) {
    size_t n = text.length();
    size_t m = pattern.length();

    std::vector<size_t> occurrences;

    for (size_t i = 0; i <= n - m;) {
        size_t j = m - 1;
        while (j >= 0 && text[i + j] == pattern[j])
            --j;

        if (j == static_cast<size_t>(-1)) {
            occurrences.emplace_back(i);
            i += gs[m];
        } else
            i += std::min(std::max(gs[j], j - bc[text[i + j]]), m);
    }

    return occurrences;
}

inline bool boyer_moore::exists(std::string &text) {
    size_t n = text.length();
    size_t m = pattern.length();

    for (size_t i = 0; i <= n - m;) {
        size_t j = m - 1;
        while (j >= 0 && text[i + j] == pattern[j])
            --j;

        if (j == static_cast<size_t>(-1))
            return true;

        i += std::min(std::max(gs[j], j - bc[text[i + j]]), m);
    }

    return false;
}
