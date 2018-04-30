#pragma once

#include <iostream>
#include "../symboltable/Symbol.h"

namespace ir {
    namespace ST = symboltable;

    class TempReg {
    public:
        TempReg(int num) : num(num) {}
        int num;
    };

    struct Label {
        ST::Symbol* name;
    };
}
