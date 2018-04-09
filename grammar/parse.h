#pragma once

#include <iostream>

namespace ast {
    namespace nodes {
        class Program;
    }
}

namespace Grammar {
    ast::nodes::Program* ParseCin();

    ast::nodes::Program* Parse(std::istream& input);

    ast::nodes::Program* Parse(std::istream* input);
}