//
// Created by Pedro Tôrres on 21/10/2018.
//

#include <climits>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>

#include "ukkonen.h"

inline void ukkonen::init_fsm(std::unordered_set<size_t> &tree, std::unordered_map<std::pair<size_t, char>, size_t> &delta, std::string &pattern, size_t &e) {
    std::unordered_map<std::vector<size_t>, size_t> index;

    size_t m = pattern.size();
    if (m <= e)
        tree.insert(0);

    std::vector<size_t> s(m + 1);
    for (size_t i = 0; i < s.size(); i++)
        s[i] = i;

    std::queue<std::unique_ptr<std::vector<size_t>, std::function<void(std::vector<size_t> *)>>> q;
    q.emplace(&s, [](std::vector<size_t> *v){});

    size_t i = 0;
    while (!q.empty()) {
        std::vector<size_t> &col = *q.front();

        for (size_t c = 0; c <= UCHAR_MAX; c++) {
            auto next = new std::vector<size_t>(pattern.size() + 1);
            for (size_t j = 1; j < next->size(); ++j)
                (*next)[j] = std::min(std::min(col[j] + 1, (*next)[j - 1] + 1), std::min(col[j - 1] + (c != pattern[j - 1]), e + 1));

            bool del = true;
            if (index.find(*next) == index.end()) {
                ++i;

                if ((*next)[m] <= e)
                    tree.insert(i);
                index[*next] = i;
                q.emplace(next, [](std::vector<size_t> *v){ delete v; });

                del = false;
            }

            delta[{index[col], c}] = index[*next];

            if (del)
                delete next;
        }

        q.pop();
    }
}

ukkonen::ukkonen(std::string &pattern, size_t edit_distance) : string_searching_algorithm(pattern), e(edit_distance) {
    ukkonen::init_fsm(this->tree, this->delta, pattern, edit_distance);
}

std::vector<size_t> ukkonen::find(std::string &text) {
    std::vector<size_t> occurrences;

    if (tree.find(0) != tree.end())
        occurrences.push_back(0);

    size_t i = 0;
    for (size_t j = 0; j < text.size(); ++j)
        if (tree.find(i = delta[{i, text[j]}]) != tree.end())
            occurrences.push_back(j);

    return occurrences;
}

bool ukkonen::exists(std::string &text) {
    if (tree.find(0) != tree.end())
        return true;

    size_t i = 0;
    for (char &c : text)
        if (tree.find(i = delta[{i, c}]) != tree.end())
            return true;

    return false;
}
