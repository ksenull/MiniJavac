#pragma once

#include <iostream>
#include "Located.h"

namespace common {
    class MiniJavacException {
    public:
        MiniJavacException(const Location& loc, const std::string& msg) : location(loc), msg(msg) {}

        explicit MiniJavacException(const std::string& msg) : MiniJavacException({}, msg) {}
        virtual ~MiniJavacException() = default;
//        MiniJavacException(const MiniJavacException&) = delete;

        std::string msg;
    private:
        Location location;

    };
}