//
// Created by Pedro Tôrres on 19/10/2018.
//

#ifndef PMT_WU_MANBER_H
#define PMT_WU_MANBER_H


#include "shift_or.h"

class wu_manber : public shift_or {
protected:
    const size_t e;

public:
    wu_manber(std::string &pattern, size_t edit_distance);
    std::vector<size_t> find(std::string &text) override;
    bool exists(std::string &text) override;
};


#endif //PMT_WU_MANBER_H
