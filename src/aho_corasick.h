#ifndef PMT_AHO_CORASICK_H
#define PMT_AHO_CORASICK_H


#include <unordered_map>
#include <vector>

#include "string_searching_algorithm.h"

namespace std {
    template<typename T1, typename T2>
    struct hash<pair<T1, T2>> {
        size_t operator()(const pair<T1, T2> &p) const {
            return hash<T1>()(p.first) ^ hash<T2>()(p.second);
        }
    };
}

namespace pmt {
    class aho_corasick : public string_searching_algorithm {
    protected:
        std::unordered_map<std::pair<size_t, char>, size_t> graph;
        std::unordered_map<size_t, std::vector<size_t>> succ;
        std::vector<size_t> fail;
        static void init_fsm(std::unordered_map<std::pair<size_t, char>, size_t> &graph, std::unordered_map<size_t, std::vector<size_t>> &succ, std::vector<size_t> &fail, std::list<std::string> &patterns);

    public:
        explicit aho_corasick(std::list<std::string> &patterns);
        std::list<size_t> find(std::string &text) override;
        bool exists(std::string &text) override;
    };
}


#endif //PMT_AHO_CORASICK_H
