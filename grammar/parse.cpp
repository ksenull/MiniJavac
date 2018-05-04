//
// Created by ksenull on 4/9/18.
//
#include "parse.h"
#include "Parser.h"
#include "Scanner.h"


namespace Grammar {

    Program ParseCin() {
        Scanner scanner(&std::cin);
        Location emptyLoc(0, 0, 0, 0);
        Program result(nullptr, nullptr, emptyLoc);
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }

    Program Parse(std::istream& input) {
        Scanner scanner(&input);
        Location emptyLoc(0, 0, 0, 0);
        Program result(nullptr, nullptr, emptyLoc);
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }

    Program Parse(std::istream* input) {
        Scanner scanner(input);
        Location emptyLoc(0, 0, 0, 0);
        Program result(nullptr, nullptr, emptyLoc);
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }
}

//int main() {
//    return 0;
//}