//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_STRING_SEARCHING_ALGORITHM_H
#define PMT_STRING_SEARCHING_ALGORITHM_H


#include <list>
#include <string>

namespace pmt {
    class string_searching_algorithm {
    public:
        const std::list<std::string> patterns;
        explicit string_searching_algorithm(std::list<std::string> &patterns);
        virtual ~string_searching_algorithm();
        virtual std::list<size_t> find(std::string &text) = 0;
        virtual bool exists(std::string &text) = 0;
    };
}


#endif //PMT_STRING_SEARCHING_ALGORITHM_H
