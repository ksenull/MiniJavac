#pragma once

#include <sstream>

namespace common {
    struct Location {
        struct Pos {
            unsigned line;
            unsigned col;

            Pos() = default;

            Pos(unsigned line, unsigned col) : line(line), col(col) {}
        };

        Pos begin;
        Pos end;

        Location() = default;

        ~Location() = default;

        Location(unsigned bl, unsigned bc, unsigned el, unsigned ec) : begin{bl, bc}, end{el, ec} {}

        std::string str() const {
            std::stringstream ss;
            ss << "line: " << begin.line << " pos: " << begin.col;
//            ss << " - ";
//            ss << "line: " << end.line << " pos: " << end.col;
            return ss.str();
        }
    };

    class Located {
        Location loc;
    public:
        Location getLoc() const { return loc; }
        Located(const Location& _loc) : loc(_loc) {};
    };
}