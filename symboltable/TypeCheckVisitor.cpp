//
// Created by ksenull on 4/28/18.
//


#include <iostream>
#include <set>
#include <cassert>

#include "TypeCheckVisitor.h"
#include "SymbolException.h"

namespace symboltable {
    namespace AN = ast::nodes;

#define COMPARE_TYPES
    void TypeCheckVisitor::visit(const AN::Identifier* node) const {
        /* nothing to check */
    }

    void TypeCheckVisitor::visit(const AN::Program* node) const {
        node->mainClass->accept(this);
        node->classDeclarationList->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::MainClass* node) const {
        currentClass = getIntern(node->name.name);
        node->st->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ClassDeclaration* node) const {
        checkCyclicClasses(node);
        currentClass = getIntern(node->id.name);
        node->localVars->accept(this);
        node->methods->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ClassDeclarationList* node) const {
        for (auto&& c : node->nodes) {
            c->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::VariableDeclarationStatementList* node) const {
        for (auto&& v : node->nodes) {
            v->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::VariableDeclarationStatement* node) const {
        node->var->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::VariableDeclaration* node) const {
        auto&& type = *node->type;
        if (type.tt == AN::TT_Object) {
            Symbol* objSymbol = getIntern(node->type->id.name);
            auto* search = symbolTable.getClassInfo(objSymbol);
            if (search == nullptr) {
                throw CantFindSymbolError(objSymbol, node->loc);
            }
        }
    }

    void TypeCheckVisitor::visit(const AN::Type* node) const {
        /* nothing to check */
    }

    void TypeCheckVisitor::visit(const AN::MethodDeclarationList* node) const {
        for (auto* method : node->nodes) {
            method->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::MethodDeclaration* node) const {
        if (node->returnType->tt == AN::TT_Object) {
            Symbol* retSymbol = getIntern(node->returnType->id.name);
            ClassInfo* classInfo = symbolTable.getClassInfo(retSymbol);
            if (classInfo == nullptr) {
                throw CantFindSymbolError(retSymbol, node->loc);
            }
        }

        curMethod = getIntern(node->id.name);
        node->statementList->accept(this);
        node->args->accept(this);
        if (node->returnExp) {
            node->returnExp->accept(this);
        }
        curMethod = nullptr;
    }

    void TypeCheckVisitor::visit(const AN::ArgumentDeclarationList* node) const {
        for (auto&& ad : node->nodes) {
            ad->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::CStatementList* node) const {
        for (auto&& s : node->nodes) {
            s->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::NestedStatement* node) const {
        node->statementList->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::IfStatement* node) const {
        checkBooleanConvertibility(node->condition);

        node->condition->accept(this);
        node->ifStatement->accept(this);
        node->elseStatement->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::WhileStatement* node) const {
        checkBooleanConvertibility(node->condition);

        node->condition->accept(this);
        node->statement->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::PrintStatement* node) const {
        checkIfInt(node->exp);
        node->exp->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::AssignStatement* node) const {
        checkIfSameType(getIntern(node->id.name), node->exp);

        node->exp->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ArrayAssignStatement* node) const {
        checkIfInt(node->arrExp);
        checkIfInt(node->exp); // array can be only of type int, so right exp should be int too

        node->arrExp->accept(this);
        node->exp->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ArgumentsList* node) const {
        for (auto* e : node->nodes) {
            e->accept(this);
        }
    }

    void TypeCheckVisitor::visit(const AN::BinopExpression* node) const {
        switch (node->type) {
            case AN::BOT_Plus:
                ;
            case AN::BOT_Minus:
                ;
            case AN::BOT_Multiply:
                ;
            case AN::BOT_Equal:
                ;
            case AN::BOT_Less:
                checkIfInt(node->left);
                checkIfInt(node->right);
                break;
            case AN::BOT_And:
                checkBooleanConvertibility(node->left);
                checkBooleanConvertibility(node->right);
                break;
            default:
                ;
        }

        node->left->accept(this);
        node->right->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ArrayItemExpression* node) const {
        checkIfInt(node->ind);

        node->arr->accept(this);
        node->ind->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ArrayLengthExpression* node) const {
        auto&& type = getExpressionType(node->arr);
        auto correctType = AN::Type(AN::TT_Array, {});
        if (areTypesDifferent(type, correctType)) {
            throw TypeError("Array expression", correctType, node->loc);
        }

        node->arr->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::CallExpression* node) const {
        // check the obj of call is a class
        Symbol* classSymbol;
        ClassInfo* classInfo;
        // only NewObjectExp and IdExp can be obj, NewObj will be checked after visiting it
        if (auto* idExp = dynamic_cast<const AN::IdExpression*>(node)) {
            classSymbol = getIntern(idExp->id.name);
            classInfo = symbolTable.getClassInfo(classSymbol);
            if (classInfo == nullptr) {
                throw CantFindSymbolError(classSymbol, classInfo->loc);
            }
        }
        else if (auto* newObjExp = dynamic_cast<const AN::NewObjectExpression*>(node)) {
            classSymbol = getIntern(newObjExp->id.name);
            classInfo = symbolTable.getClassInfo(classSymbol);
            if (classInfo == nullptr) {
                throw CantFindSymbolError(classSymbol, classInfo->loc);
            }
        }
        else {
            throw TypeError("Object of call", AN::Type(AN::TT_Object, "", {}), node->loc);
        }

        // check that the class has such method
        auto* methodSymbol = getIntern(node->method.name);
        auto* methodInfo = classInfo->getMethodInfo(methodSymbol);
        if (methodInfo == nullptr) {
            throw CantFindSymbolError(methodSymbol, node->loc);
        }

        // check if args are compatible with signature
        auto&& correctArgsList = methodInfo->getArgsList();
        size_t correctArgsCount = correctArgsList.size();
        size_t argsCount = node->args->nodes.size();
        if (correctArgsCount != argsCount) {
            throw MethodCantbeAppliedError(methodSymbol, methodInfo);
        }
        for (int i = 0; i < argsCount; i++) { // arg - expression
            auto* arg =node->args->nodes[i];
            if (auto* exp = dynamic_cast<AN::IExpression*>(arg)) {

                std::pair<Symbol*, VariableInfo*> correctArg = methodInfo->getArgsList()[i];
                auto* correctType = correctArg.second->getType();
                auto&& type = getExpressionType(exp);
                if (areTypesDifferent(type, *correctType)) {
                    throw MethodCantbeAppliedError(methodSymbol, methodInfo);
                }
            }
        }

        node->obj->accept(this);
        node->args->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ConstExpression* node) const {
        /* nothing to check */
    }

    void TypeCheckVisitor::visit(const AN::BoolExpression* node) const {
        /* nothing to check */
    }

    void TypeCheckVisitor::visit(const AN::IdExpression* node) const {
        /* nothing to check */
    }

    void TypeCheckVisitor::visit(const AN::NewArrayExpression* node) const {
        checkIfInt(node->exp);

        node->exp->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::NewObjectExpression* node) const {
        auto* symbol = getIntern(node->id.name);
        auto* classInfo = symbolTable.getClassInfo(symbol);
        if (classInfo == nullptr) {
            throw CantFindSymbolError(symbol, node->loc);
        }
    }

    void TypeCheckVisitor::visit(const AN::NotExpression* node) const {
        checkBooleanConvertibility(node->exp);

        node->exp->accept(this);
    }

    void TypeCheckVisitor::checkCyclicClasses(const AN::ClassDeclaration* classDeclaration) const {
        Symbol* baseSymbol = getIntern(classDeclaration->base.name);

        std::set<Symbol*> visited;

        while (not baseSymbol->name.empty()) {
            auto* baseInfo = symbolTable.getClassInfo(baseSymbol);
            if (baseInfo == nullptr) {
                return;
            }

            if (visited.find(baseSymbol) != visited.end()) {
                throw CyclicInheritanceError(baseSymbol, baseInfo->loc, classDeclaration->loc);
            }
            visited.emplace(baseSymbol);

            if (auto* base = baseInfo->getBase()) {
                baseSymbol = getIntern(base->name);
            }
        }
    }

    void TypeCheckVisitor::checkBooleanConvertibility(const AN::IExpression* exp) const {
        // according to grammar all expression ar eboolean convertible except void Call()
        if (auto* call = dynamic_cast<const AN::CallExpression*>(exp)) {
            if (auto* callClass = dynamic_cast<AN::IdExpression*>(call->obj)) {
                auto* callClassSymbol = getIntern(callClass->id.name);
                auto* callClassInfo = symbolTable.getClassInfo(callClassSymbol);

                auto* callMethodSymbol = getIntern(call->method.name);
                auto* methodInfo = callClassInfo->getMethodInfo(callMethodSymbol);
//                if (methodInfo == nullptr) {
//                    throw CantFindSymbolError()
//                }
                auto* type = methodInfo->getReturnType();
                if (type->tt == AN::TT_Void) {
                    throw TypeError(callMethodSymbol, *type, methodInfo->loc);
                }
            }

        }
    }

    void TypeCheckVisitor::checkIfInt(const AN::IExpression* exp) const {
        if (dynamic_cast<const AN::ConstExpression*>(exp)) {
            return;
        }
        if (auto* binop = dynamic_cast<const AN::BinopExpression*>(exp)) {
            if (binop->type == AN::BOT_Plus || binop->type == AN::BOT_Minus
                || binop->type == AN::BOT_Multiply) {
                checkIfInt(binop->left);
                checkIfInt(binop->right);
                return;
            }
            else {
                throw TypeError(getIntern("Expression "), AN::Type(AN::TT_Int, {}), exp->loc);
            }
        }
        if (auto* arrItem = dynamic_cast<const AN::ArrayItemExpression*>(exp)) {
            return;
        }
        if (auto* arrLength = dynamic_cast<const AN::ArrayLengthExpression*>(exp)) {
            return;
        }
        if (auto* idExp = dynamic_cast<const AN::IdExpression*>(exp)) {
            Symbol* symbol = getIntern(idExp->id.name);

            if (idExp->isThis) {
                throw TypeError(getIntern("Expression "), AN::Type(AN::TT_Int, {}), exp->loc);
            }

            auto* classInfo = symbolTable.getClassInfo(currentClass);

            auto* search = classInfo->getVariableInfo(symbol);
            if (search != nullptr) {
                auto* type = search->getType();
                if (type->tt != AN::TT_Int) {
                    throw TypeError(getIntern("Expression "), AN::Type(AN::TT_Int, {}), exp->loc);
                }
                else {
                    return;
                }
            }

            if (curMethod != nullptr) {
                auto* curMethodInfo = classInfo->getMethodInfo(curMethod);
                search = curMethodInfo->getVariableInfo(symbol);

                if (search != nullptr) {
                    auto* type = search->getType();
                    if (type->tt != AN::TT_Int) {
                        throw TypeError(getIntern("Expression "), AN::Type(AN::TT_Int, {}),
                                        exp->loc);
                    }
                }
            }
        }
    }

    bool TypeCheckVisitor::areTypesDifferent(const AN::Type& type, const AN::Type& correctType) const {
        return (type.tt != correctType.tt || (type.tt == AN::TT_Object && correctType.tt == AN::TT_Object &&
                                              getIntern(type.id.name) != getIntern(correctType.id.name)));
    }

    void TypeCheckVisitor::checkIfSameType(Symbol* left, AN::IExpression* exp) const {
        if (symbolTable.getClassInfo(left) != nullptr) {
            if (auto* idExp = dynamic_cast<AN::IdExpression*>(exp)) {
                if (idExp->isThis) return;

                auto* rightSymbol = getIntern(idExp->id.name);
                auto* rightClassInfo = symbolTable.getClassInfo(rightSymbol);
                if (rightClassInfo == nullptr) {
                    throw ExpressionTypeError(rightSymbol, left, exp->loc);
                }
                return;
            }
            if (auto* newObjExp = dynamic_cast<AN::NewObjectExpression*>(exp)) {
                auto* symb = getIntern(newObjExp->id.name); // TODO also could be base
                auto* rightClassInfo = symbolTable.getClassInfo(symb);
                if (rightClassInfo == nullptr) {
                    throw ExpressionTypeError(symb, left, exp->loc);
                }
                return;
            }
            throw ExpressionTypeError(left, exp->loc);
        }

        auto* curClassInfo = symbolTable.getClassInfo(currentClass);

        auto* leftInfo = curClassInfo->getVariableInfo(left);
        if (left == nullptr) {
            assert(curMethod != nullptr);
            auto* curMethodInfo = curClassInfo->getMethodInfo(curMethod);
            leftInfo = curMethodInfo->getVariableInfo(left);
            auto* leftType = leftInfo->getType();
        }
        // TODO int
        // int array
        // boolean convertible
    }


    AN::Type TypeCheckVisitor::getExpressionType(AN::IExpression* exp) const {
        if (dynamic_cast<AN::ConstExpression*>(exp)) {
            return AN::Type(AN::TT_Int, {});
        }
        if (dynamic_cast<AN::BoolExpression*>(exp)) {
            return AN::Type(AN::TT_Bool, {});
        }
        if (dynamic_cast<AN::ArrayItemExpression*>(exp)) {
            return AN::Type(AN::TT_Int, {});
        }
        if (dynamic_cast<AN::ArrayLengthExpression*>(exp)) {
            return AN::Type(AN::TT_Int, {});
        }
        if (dynamic_cast<AN::NewArrayExpression*>(exp)) {
            return AN::Type(AN::TT_Array, {});
        }
        if (auto* obj = dynamic_cast<AN::NewObjectExpression*>(exp)) {
            return AN::Type(AN::TT_Object, obj->id, {});
        }
        if (auto* binop = dynamic_cast<AN::BinopExpression*>(exp)) {
            if (binop->type == AN::BOT_Plus || binop->type == AN::BOT_Minus || binop->type == AN::BOT_Multiply) {
                // TODO
            }
        }
        return AN::Type(AN::TT_Int, {});
    }

}
