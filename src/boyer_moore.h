//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_BOYER_MOORE_H
#define PMT_BOYER_MOORE_H


#include "string_searching_algorithm.h"

class boyer_moore : public string_searching_algorithm {
protected:
    std::vector<size_t> bc;
    std::vector<size_t> gs;
    static void init_border(std::vector<size_t> &v, std::string &pattern);
    static void init_good_suffix(std::vector<size_t> &v, std::string &pattern);
    static void init_bad_char(std::vector<size_t> &v, std::string &pattern);

public:
    explicit boyer_moore(std::string &pattern);
    std::vector<size_t> find(std::string &text) override;
    bool exists(std::string &text) override;
};


#endif //PMT_BOYER_MOORE_H
