//
// Created by ksenull on 4/30/18.
//
#include "Temp.h"

namespace frames {
    std::string Temp::str() const
    {
        if(address == 0) {
            return "offset " + std::to_string(offset);
        }
        return "address: " + std::to_string(getAddress()) + ", " +
               "offset: " + std::to_string(offset);
    }
}
