//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_STRING_SEARCHING_ALGORITHM_H
#define PMT_STRING_SEARCHING_ALGORITHM_H


#include <string>
#include <vector>

class string_searching_algorithm {
public:
    const std::string pattern;
    explicit string_searching_algorithm(std::string &pattern);
    virtual ~string_searching_algorithm();
    virtual std::vector<size_t> find(std::string &text) = 0;
    virtual bool exists(std::string &text) = 0;
};


#endif //PMT_STRING_SEARCHING_ALGORITHM_H
