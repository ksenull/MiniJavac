#pragma once

#include <iostream>

namespace frames {
    class Temp {
    public:
        Temp(int offset, int address) : offset(offset), address(address) {}
        Temp(int offset = 0) : Temp(offset, 0) {}

        int getAddress() const {
            return address + offset;
        }
        Temp AtAddress(int _address) const {
            return Temp(offset, _address + address);
        }
        std::string str() const;
    private:
        const int offset;
        int address;
    };
}
