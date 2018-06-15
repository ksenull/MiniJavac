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
        currentClass = getIntern(node->id->name);
        node->st->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::ClassDeclaration* node) const {
        if (node->base) {
            checkCyclicClasses(node);
        }
        currentClass = getIntern(node->id->name);
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
            Symbol* objSymbol = getIntern(node->type->id->name);
            auto* search = symbolTable.getClassInfo(objSymbol);
            if (search == nullptr) {
                throw CantFindSymbolError(objSymbol, node->getLoc());
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
        curMethod = getIntern(node->id->name);

        // check if return type exists
        if (node->returnType->tt == AN::TT_Object) {
            Symbol* retSymbol = getIntern(node->returnType->id->name);
            ClassInfo* classInfo = symbolTable.getClassInfo(retSymbol);
            if (classInfo == nullptr) {
                throw CantFindSymbolError(retSymbol, node->getLoc());
            }
        }

        // check if return exp is of type ret exp
        if (node->returnExp) {
            auto&& retExpType = getExpressionType(node->returnExp);
            auto&& correctType = TypeInfo(node->returnType);
            if (!retExpType.first || !(retExpType.second == correctType)) {
                throw TypeError("Return expression", correctType, node->returnExp->getLoc());
            }
        }

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
        auto&& typeLeft = getIdType(node->id);
        auto&& typeRight = getExpressionType(node->exp);
        if (!typeLeft.first || !typeRight.first || !(typeRight.second == typeLeft.second)) {
            throw ExpressionTypeError(getIntern(node->id->name), typeLeft.second, typeRight.second, node->getLoc());
        }

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
        auto correctType = TypeInfo(VT_IntArray);
        if (!type.first || !(type.second == correctType)) {
            throw TypeError("Array expression", correctType, node->getLoc());
        }

        node->arr->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::CallExpression* node) const {
        // check the obj of call is a class
        Symbol* classSymbol;
        ClassInfo* classInfo;
        // only NewObjectExp and IdExp can be obj, NewObj will be checked after visiting it
        if (auto* idExp = dynamic_cast<const AN::IdExpression*>(node->obj)) {
            if (idExp->isThis) {
                classSymbol = currentClass;
            }
            else {
                auto* idSymbol = getIntern(idExp->id->name);
                auto* curClassInfo = symbolTable.getClassInfo(currentClass);
                auto* varInfo = curClassInfo->getVariableInfo(idSymbol);
                if (varInfo == nullptr) {
                    auto* methodInfo = curClassInfo->getMethodInfo(curMethod);
                    varInfo = methodInfo->getVariableInfo(idSymbol);
                    if (varInfo == nullptr) {
                        throw CantFindSymbolError(idSymbol, node->obj->getLoc());
                    }
                }
                if (varInfo->getType().type != VT_Object) {
                    throw TypeError("Object of call", TypeInfo(VT_Object), node->getLoc());
                }
                classSymbol = varInfo->getType().classname;
            }
            classInfo = symbolTable.getClassInfo(classSymbol); // classInfo for next check
            if (classInfo == nullptr) {
                throw CantFindSymbolError(classSymbol, node->obj->getLoc());
            }
        }
        else if (auto* newObjExp = dynamic_cast<const AN::NewObjectExpression*>(node->obj)) {
            classSymbol = getIntern(newObjExp->id->name);
            classInfo = symbolTable.getClassInfo(classSymbol);
            if (classInfo == nullptr) {
                throw CantFindSymbolError(classSymbol, node->obj->getLoc());
            }
        }
        else {
            throw TypeError("Object of call", TypeInfo(VT_Object), node->getLoc());
        }

        // check that the class has such method
        auto* methodSymbol = getIntern(node->method->name);
        auto* methodInfo = classInfo->getMethodInfo(methodSymbol);
        if (methodInfo == nullptr) {
            throw CantFindSymbolError(methodSymbol, node->getLoc());
        }

        // check if args are compatible with signature
        auto&& correctArgsList = methodInfo->getArgsList();
        size_t correctArgsCount = correctArgsList.size();
        size_t argsCount = node->args->nodes.size();
        if (correctArgsCount != argsCount) {
            throw MethodCantbeAppliedError(methodSymbol, methodInfo, node->getLoc());
        }
        for (int i = 0; i < argsCount; i++) { // arg - expression
            auto* arg =node->args->nodes[i];
            if (auto* exp = dynamic_cast<AN::IExpression*>(arg)) {

                std::pair<Symbol*, VariableInfo*> correctArg = methodInfo->getArgsList()[i];
                auto&& correctType = TypeInfo(correctArg.second->getType());
                auto&& type = getExpressionType(exp);
                if (!type.first || !(type.second == correctType)) {
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
        if (node->isThis) {
            return;
        }
        auto* curClassInfo = symbolTable.getClassInfo(currentClass);
        auto* idSymbol = getIntern(node->id->name);
        auto* varInfo = curClassInfo->getVariableInfo(idSymbol);
        if (varInfo == nullptr) {
            auto* methodInfo = curClassInfo->getMethodInfo(curMethod);
            varInfo = methodInfo->getVariableInfo(idSymbol);
            if (varInfo == nullptr) {
                throw CantFindSymbolError(idSymbol, node->getLoc());
            }
        }
    }

    void TypeCheckVisitor::visit(const AN::NewArrayExpression* node) const {
        checkIfInt(node->exp);

        node->exp->accept(this);
    }

    void TypeCheckVisitor::visit(const AN::NewObjectExpression* node) const {
        auto* symbol = getIntern(node->id->name);
        auto* classInfo = symbolTable.getClassInfo(symbol);
        if (classInfo == nullptr) {
            throw CantFindSymbolError(symbol, node->getLoc());
        }
    }

    void TypeCheckVisitor::visit(const AN::NotExpression* node) const {
        checkBooleanConvertibility(node->exp);

        node->exp->accept(this);
    }

    void TypeCheckVisitor::checkCyclicClasses(const AN::ClassDeclaration* classDeclaration) const {
        assert(classDeclaration->base);

        auto* baseSymbol = getIntern(classDeclaration->base->name);

        std::set<Symbol*> visited;

        while (baseSymbol) {
            auto* baseInfo = symbolTable.getClassInfo(baseSymbol);
            if (baseInfo == nullptr) {
                return;
            }

            if (visited.find(baseSymbol) != visited.end()) {
                throw CyclicInheritanceError(baseSymbol, baseInfo->getLoc(), classDeclaration->getLoc());
            }
            visited.emplace(baseSymbol);

            baseSymbol = baseInfo->getBase();
        }
    }

    void TypeCheckVisitor::checkBooleanConvertibility(const AN::IExpression* exp) const {
        auto&& expType = getExpressionType(exp);
        if (!expType.first || !expType.second.isBool()) {
            throw TypeError("Condition", expType.second, exp->getLoc());
        }
    }

    void TypeCheckVisitor::checkIfInt(const AN::IExpression* exp) const {
        auto&& type = getExpressionType(exp);
        if (!type.first || !type.second.isInt()) {
            throw TypeError(getIntern("Expression "), TypeInfo(VT_Int), exp->getLoc());
        }
    }

    std::pair<bool, TypeInfo> TypeCheckVisitor::getExpressionType(const AN::IExpression* exp) const {
        if (dynamic_cast<const AN::ConstExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_Int));
        }
        if (dynamic_cast<const AN::BoolExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_Boolean));
        }
        if (dynamic_cast<const AN::ArrayItemExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_Int));
        }
        if (dynamic_cast<const AN::ArrayLengthExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_Int));
        }
        if (dynamic_cast<const AN::NewArrayExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_IntArray));
        }
        if (auto* obj = dynamic_cast<const AN::NewObjectExpression*>(exp)) {
            return std::make_pair(true, TypeInfo(VT_Object, getIntern(obj->id->name)));
        }
        if (auto* binop = dynamic_cast<const AN::BinopExpression*>(exp)) {
            if (binop->type == AN::BOT_Plus || binop->type == AN::BOT_Minus || binop->type == AN::BOT_Multiply) {
                auto&& leftType = getExpressionType(binop->left);
                auto&& rightType = getExpressionType(binop->right);
                return std::make_pair(leftType.first && rightType.first &&
                                      leftType.second.isInt() && rightType.second.isInt(), TypeInfo(VT_Int));
            }
            if (binop->type == AN::BOT_Less || binop->type == AN::BOT_Equal) {
                auto&& leftType = getExpressionType(binop->left);
                auto&& rightType = getExpressionType(binop->right);
                return std::make_pair(leftType.first && rightType.first &&
                                      leftType.second.isInt() && rightType.second.isInt(), TypeInfo(VT_Boolean));
            }
            if (binop->type == AN::BOT_And) {
                auto&& leftType = getExpressionType(binop->left);
                auto&& rightType = getExpressionType(binop->right);
                return std::make_pair(leftType.first && rightType.first &&
                                      leftType.second.isBool() &&
                                      rightType.second.isBool(), TypeInfo(VT_Boolean));
            }
            else {
                return std::make_pair(false, TypeInfo{});
            }
        }

        if (auto* callExp = dynamic_cast<const AN::CallExpression*>(exp)) {
            auto&& objType = getExpressionType(callExp->obj);
            if (objType.first && objType.second.type == VT_Object) {
                auto* objSymbol = objType.second.classname;
                auto* objInfo = symbolTable.getClassInfo(objSymbol);
                if (objInfo == nullptr) {
                    return std::make_pair(false, TypeInfo{});
                }
                auto* methodSymbol = getIntern(callExp->method->name);
                auto* methodInfo = objInfo->getMethodInfo(methodSymbol);
                if (methodInfo == nullptr) {
                    return std::make_pair(false, TypeInfo{});
                }
                return std::make_pair(true, methodInfo->getReturnType());
            }
            else {
                return std::make_pair(false, TypeInfo{});
            }
        }

        if (auto* idExp = dynamic_cast<const AN::IdExpression*>(exp)) {
            if (idExp->isThis) {
                return std::make_pair(true, TypeInfo(VT_Object, currentClass));
            }
            return getIdType(idExp->id);
        }

        if (auto* notExp = dynamic_cast<const AN::NotExpression*>(exp)) {
            auto&& innerExpType = getExpressionType(notExp->exp);
            return std::make_pair(innerExpType.first && innerExpType.second.isBool(), TypeInfo(VT_Boolean));
        }

        return std::make_pair(false, TypeInfo{});
    }

    std::pair<bool, TypeInfo> TypeCheckVisitor::getIdType(const ast::nodes::Identifier* id) const {
        auto* curClassInfo = symbolTable.getClassInfo(currentClass);
        auto* idSymbol = getIntern(id->name);
        auto* varInfo = curClassInfo->getVariableInfo(idSymbol);
        if (varInfo == nullptr) {
            if (curMethod == nullptr) {
                return std::make_pair(false, TypeInfo{});
            }
            auto* methodInfo = curClassInfo->getMethodInfo(curMethod);
            varInfo = methodInfo->getVariableInfo(idSymbol);
            if (varInfo == nullptr) {
                return std::make_pair(false, TypeInfo{});
            }
            return std::make_pair(true, TypeInfo(varInfo->getType()));
        }
        return std::make_pair(true, TypeInfo(varInfo->getType()));
    }

}
