//
// Created by ksenull on 4/9/18.
//
#include "parse.h"
#include "Parser.h"
#include "Scanner.h"


namespace Grammar {

    Program* ParseCin() {
        Scanner scanner(&std::cin);
        Program* result;
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }

    Program* Parse(std::istream& input) {
        Scanner scanner(&input);
        Program* result;
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }

    Program* Parse(std::istream* input) {
        Scanner scanner(input);
        Program* result;
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }
}