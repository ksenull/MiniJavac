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
}