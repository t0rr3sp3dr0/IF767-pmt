#ifndef PMT_WU_MANBER_H
#define PMT_WU_MANBER_H


#include "shift_or.h"

namespace pmt {
    class wu_manber : public shift_or {
    protected:
        const size_t e;

    public:
        wu_manber(std::list<std::string> &patterns, size_t edit_distance);
        std::list<size_t> find(std::string &text) override;
        bool exists(std::string &text) override;
    };
}


#endif //PMT_WU_MANBER_H
