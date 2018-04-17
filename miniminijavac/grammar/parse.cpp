//
// Created by ksenull on 4/9/18.
//
#include "parse.h"
#include "Parser.h"
#include "Scanner.h"
#include <unistd.h>

namespace Grammar {

    Program ParseCin() {
        Scanner scanner(&std::cin);
        Program result;
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }

    Program Parse(std::istream& input) {
        Scanner scanner(&input);
        Program result;
        Parser parser(scanner, result);
        usleep(100000);
        parser.parse();
        usleep(100000);
        return result;
    }

    Program Parse(std::istream* input) {
        Scanner scanner(input);
        Program result;
        Parser parser(scanner, result);
        parser.parse();
        return result;
    }
}

//int main() {
//    return 0;
//}