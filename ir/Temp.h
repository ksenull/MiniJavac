#pragma once

#include <iostream>
#include "../symboltable/Symbol.h"

namespace ir {
    namespace ST = symboltable;

    class TempReg {
    public:
        explicit TempReg(int num) : num(num) {}
        int num;
    };

    struct Label {
        explicit Label(ST::Symbol* symbol) : name(symbol) {}
        explicit Label(const std::string& str) : name(ST::getIntern(str)) {}

        ST::Symbol* name;
    };
}
