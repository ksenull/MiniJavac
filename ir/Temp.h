#pragma once

#include <iostream>
#include "../symboltable/Symbol.h"

namespace ir {

    struct IReg {
        virtual ~IReg() = default;
    };

    class TempReg : public IReg {
    public:
        TempReg() : num(counter) {
            counter++;
        }
        int num{};
    private:
        static int counter;
    };

    class SpecialReg : public IReg {
    public:
        explicit SpecialReg(int addr) : addr(addr) {}
        int addr;
    };


    using Label = symboltable::Symbol;
}
