#pragma once

#include "../common/Exception.h"
#include "Symbol.h"
#include "../ast/nodes/Nodes.h"

namespace symboltable {

    using BaseException = common::MiniJavacException;
    using Location = common::Location;

    struct DuplicateClassError : BaseException {
        DuplicateClassError(Symbol* symbol, const Location& oldLoc, const Location& duplicateLoc) : BaseException(
                duplicateLoc, "Duplicate Error: " + duplicateLoc.str() + ". Class " + symbol->name +
                              " previously declared here: " + oldLoc.str()) {}
    };

    struct CantFindSymbolError : BaseException {
        CantFindSymbolError(Symbol* symbol, const Location& loc) :
                BaseException(loc, "Can't find symbol " + symbol->name + ": " + loc.str()) {}
    };

    struct VariableAlreadyDefinedError : BaseException {
        VariableAlreadyDefinedError(Symbol* symbol, const Location& oldLoc, const Location& loc) :
                BaseException(loc, "Variable " + symbol->name + " is already defined here: " + oldLoc.str()) {}
    };

    struct MethodAlreadyDefinedError : BaseException {
        MethodAlreadyDefinedError(Symbol* symbol, const Location& oldLoc, const Location& loc) :
                BaseException(loc, "Method " + symbol->name + "() is already defined here: " + oldLoc.str()) {}
    };

}