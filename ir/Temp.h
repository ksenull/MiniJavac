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
        enum Type {
            SRT_FP,
            SRT_SP,
            SRT_RV
        };
        explicit SpecialReg(Type _type, int _addr) : type(_type), addr(_addr) {}
//        explicit SpecialReg(int addr) : addr(addr) {}
        int addr;
        Type type;
    };


    using Label = symboltable::Symbol;

    class SpecialLabel : public Label {
    public:
        SpecialLabel(std::string _name) : Label(std::move(_name) + "__" + std::to_string(counter)) {
            counter++;
        }

    private:
        static int counter;
    };
}
