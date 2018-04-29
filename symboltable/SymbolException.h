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

    struct CyclicInheritanceError : BaseException {
        CyclicInheritanceError(Symbol* symbol, const Location& cycleRootLoc, const Location& loc) :
                BaseException(loc, "Cyclic Inheritance Error in class " + symbol->name +
                        " with root defined here: " + cycleRootLoc.str()) {}
    };

    struct TypeError : BaseException {
        TypeError(Symbol* symbol, const ast::nodes::Type& type, const Location& loc) :
                BaseException(loc, "Type Error: " + symbol->name +
                        " should be of type " + type.getTT() + ": " + loc.str()) {}

        TypeError(const std::string& objectDescription, const ast::nodes::Type& type, const Location& loc) :
                BaseException(loc, "Type Error: " + objectDescription +
                " should be of type " + type.getTT() + ": " + loc.str()) {}
    };

    struct ExpressionTypeError : BaseException {
        ExpressionTypeError(Symbol* symbol, const ast::nodes::Type& leftType,
                            const ast::nodes::Type& rightType, const Location& loc) :
                BaseException(loc, "TypeError: Expression operands should be of same type. Having: " +
                leftType.getTT() + " and " + rightType.getTT() + " here: " + loc.str()) {}

        ExpressionTypeError(Symbol* right, Symbol* leftClass, const Location& loc) :
                BaseException(loc, "Type mismatch: Right symbol " + right->name + "should be of type " + leftClass->name +
                ": " + loc.str()) {}

        ExpressionTypeError(Symbol* left, const Location& loc) :
                BaseException(loc, "Type mismatch: Right symbol should be whether of type " + left->name +
                        "whether new " + left->name + "(): " + loc.str()){}
    };

    struct MethodCantbeAppliedError : BaseException {
        MethodCantbeAppliedError(Symbol* methodName, MethodInfo* methodInfo, const Location& loc) :
                BaseException(loc, "Method " + methodName->name + "() cannot be applied. Operands type mismatch: "
                                               + loc.str()) {}
        MethodCantbeAppliedError(Symbol* methodName, MethodInfo* methodInfo) :
                MethodCantbeAppliedError(methodName, methodInfo, methodInfo->loc) {}
    };

}