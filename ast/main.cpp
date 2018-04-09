#include <iostream>
#include "PrintVisitor.h"
#include "../grammar/parse.h"


int main() {
    ast::nodes::Program* program;
    program = Grammar::ParseCin();
    return 0;
}