#pragma once

#include <iostream>

namespace ast {
//    namespace nodes {
        class Program;
//    }
}

namespace Grammar {
    ast::Program* ParseCin();

    ast::Program* Parse(std::istream& input);

    ast::Program* Parse(std::istream* input);
}
