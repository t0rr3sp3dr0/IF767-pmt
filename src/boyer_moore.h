#ifndef PMT_BOYER_MOORE_H
#define PMT_BOYER_MOORE_H


#include <vector>

#include "string_searching_algorithm.h"

namespace pmt {
class boyer_moore : public string_searching_algorithm {
    protected:
        std::list<std::vector<size_t>> bcs;
        std::list<std::vector<size_t>> gss;
        static void init_border(std::vector<size_t> &v, std::string &pattern);
        static void init_good_suffix(std::vector<size_t> &v, std::string &pattern);
        static void init_bad_char(std::vector<size_t> &v, std::string &pattern);

    public:
        explicit boyer_moore(std::list<std::string> &patterns);
        std::list<size_t> find(std::string &text) override;
        bool exists(std::string &text) override;
    };
}


#endif //PMT_BOYER_MOORE_H
