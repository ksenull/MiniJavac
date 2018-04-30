#pragma once

#include <iostream>

namespace frames {
    class Temp {
    public:
        Temp(int offset) : offset(offset) {}
    private:
        const int offset;
    };

    class TempReg {
    public:
        TempReg(int num) : num(num) {}
    private:
        int num;
    };
}
