#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <sstream>
#include <vector>

#include <getopt.h>

#include "string_searching_algorithm.h"
#include "aho_corasick.h"
#include "boyer_moore.h"
#include "shift_or.h"
#include "wu_manber.h"

enum algorithm {
    AHO_CORASICK = 'a',
    BOYER_MOORE  = 'b',
    SHIFT_OR     = 's',
    UKKONEN      = 'u',
    WU_MANBER    = 'w',
};

enum mode {
    DEFAULT = 0x00,
    COUNT   = 0x01,
    QUIET   = 0x10,
};

void help(char *s) {
    std::cerr
            << "Usage: " << s << " [OPTION]... PATTERN [FILE]..." << std::endl
            << "Search for PATTERN in each FILE." << std::endl
            << "Example: " << s << " 'hello world' menu.h main.c" << std::endl
            << std::endl
            << "Pattern selection and interpretation:" << std::endl
            << "  -a, --algorithm A     use A (aho-corasick, boyer-moore, shift-or, ukkonen, or wu-manber) as matching algorithm" << std::endl
            << "  -e, --edit E          set E as max edit distance (only if algorithm is ukkonen or wu-manber)" << std::endl
            << "  -p, --pattern FILE    obtain PATTERN from FILE" << std::endl
            << std::endl
            << "Miscellaneous:" << std::endl
            << "  -h, --help            display this help text and exit" << std::endl
            << std::endl
            << "Output control:" << std::endl
            << "  -c, --count           print only a count of selected lines per FILE" << std::endl
            << "  -q, --quiet           suppress all normal output" << std::endl
            ;
}

int main(int argc, char *argv[]) {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    const char *short_options = "a:e:p:cqh";
    const option long_options[] = {
            {"algorithm", required_argument, nullptr, 'a'},
            {"edit",      required_argument, nullptr, 'e'},
            {"pattern",   required_argument, nullptr, 'p'},
            {"count",     no_argument,       nullptr, 'c'},
            {"quiet",     no_argument,       nullptr, 'q'},
            {"help",      no_argument,       nullptr, 'h'},
            {nullptr,     no_argument,       nullptr, '\0'},
    };
    int option_index = -1;

    algorithm a = BOYER_MOORE;
    size_t e = 0;
    size_t m = mode::DEFAULT;

    std::list<std::string> p;
    std::queue<std::unique_ptr<std::istream, std::function<void(std::istream *)>>> t;

    int c;
    while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1)
        switch (c) {
            case 'a': {
                a = static_cast<algorithm>(optarg[0]);
                break;
            }

            case 'e': {
                std::stringstream(optarg) >> e;
                break;
            }

            case 'p': {
                std::ifstream ifs(optarg);
                std::string s;
                while (ifs >> s)
                    p.emplace_back(s);
                break;
            }

            case 'c': {
                m |= mode::COUNT;
                break;
            }

            case 'q': {
                m |= mode::QUIET;
                break;
            }

            case 'h':
            case '?':
            default: {
                help(argv[0]);
                return EXIT_FAILURE;
            }
        }

    for (auto i = static_cast<size_t>(optind); i < argc; ++i) {
        if (p.empty())
            p.emplace_back(argv[i]);
        else
            t.emplace(new std::ifstream(argv[i]), [](std::istream *v) { delete v; });
    }
    if (t.empty())
        t.emplace(&std::cin, [](std::istream *) {});

    if (p.empty()) {
        help(argv[0]);
        return EXIT_FAILURE;
    }

    std::list<std::unique_ptr<string_searching_algorithm>> matchers;
    switch (a) {
        case AHO_CORASICK:
            for (std::string &pattern : p)
                matchers.emplace_back(new aho_corasick(pattern));
            break;

        case BOYER_MOORE:
            for (std::string &pattern : p)
                matchers.emplace_back(new boyer_moore(pattern));
            break;

        case SHIFT_OR:
            for (std::string &pattern : p)
                matchers.emplace_back(new shift_or(pattern));
            break;

        case WU_MANBER:
            for (std::string &pattern : p)
                matchers.emplace_back(new wu_manber(pattern, e));
            break;

        default:
            help(argv[0]);
            return EXIT_FAILURE;
    }

    while (!t.empty()) {
        std::istream &is = *t.front();

        std::string text;
        while (getline(is, text)) {
            if (!is.eof())
                text += '\n';

            for (auto &matcher : matchers) {
                if (text.length() < matcher->pattern.length())
                    continue;

                if (m & mode::COUNT) {
                    std::vector<size_t> occurrences = matcher->find(text);

                    if (!(m & mode::QUIET)) {
                        for (auto &i : occurrences)
                            std::cout << '\t' << i << std::endl;

                        if (!occurrences.empty())
                            std::cout << text;
                    }
                } else if (matcher->exists(text) && !(m & mode::QUIET)) {
                    std::cout << text;

                    if (is.eof())
                        std::cout << std::endl;
                }
            }
        }

        t.pop();
    }

    return EXIT_SUCCESS;
}
