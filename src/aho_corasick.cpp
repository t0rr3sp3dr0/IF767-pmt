#include <climits>
#include <queue>

#include "aho_corasick.h"

inline void pmt::aho_corasick::init_fsm(std::unordered_map<std::pair<size_t, char>, size_t> &graph, std::unordered_map<size_t, std::vector<size_t>> &succ, std::vector<size_t> &fail, std::list<std::string> &patterns) {
    size_t i = 0;
    for (auto &p : patterns) {
        size_t cur = 0;
        for (auto &c : p) {
            std::pair<char, size_t> key = {cur, c};
            if (graph.find(key) != graph.end())
                cur = graph[key];
            else
                graph[key] = cur = graph.size();
        }

        succ[cur].emplace_back(i++);
    }

    fail.resize(graph.size());

    std::queue<size_t> q;
    for (size_t c = 0; c <= UCHAR_MAX; c++) {
        size_t state = graph[{0, c}];
        if (state != 0)
            q.push(state);
    }

    while (!q.empty()) {
        size_t state = q.front();
        q.pop();

        for (size_t c = 0; c <= UCHAR_MAX; c++)
            if (graph.find({state, c}) != graph.end()) {
                size_t next = graph[{state, c}];
                q.push(next);

                size_t cur = fail[state];
                while (graph.find({cur, c}) == graph.end())
                    cur = fail[cur];

                fail[next] = graph[{cur, c}];
                succ[next].insert(succ[next].end(), succ[fail[next]].begin(), succ[fail[next]].end());
            }
    }
}

pmt::aho_corasick::aho_corasick(std::list<std::string> &patterns) : string_searching_algorithm(patterns) {
    init_fsm(this->graph, this->succ, this->fail, patterns);
}

std::list<size_t> pmt::aho_corasick::find(std::string &text) {
    std::vector<size_t> m;
    for (auto &p: patterns)
        m.emplace_back(p.size());

    std::list<size_t> occurrences;

    size_t cur = 0;
    size_t i = 0;
    for (auto &c : text) {
        while (graph.find({cur, c}) == graph.end())
            cur = fail[cur];
        cur = graph[{cur, c}];

        for (auto &p: succ[cur])
            occurrences.emplace_back(i - m[p] + 1);
        ++i;
    }

    return occurrences;
}

bool pmt::aho_corasick::exists(std::string &text) {
    size_t cur = 0;
    size_t i = 0;
    for (auto &c: text) {
        while (graph.find({cur, c}) == graph.end())
            cur = fail[cur];
        cur = graph[{cur, c}];

        if (!succ[cur].empty())
            return true;
        ++i;
    }

    return false;
}
