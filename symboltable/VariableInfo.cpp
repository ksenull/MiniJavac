//
// Created by ksenull on 4/25/18.
//
#include "VariableInfo.h"
#include "SymbolException.h"
#include "../ast/nodes/Nodes.h"

namespace symboltable {
    namespace AN = ast::nodes;

    void VariableInfo::BuildFromAst(ast::nodes::VariableDeclaration* var) {
        typeInfo = TypeInfo(var->type);
        if (typeInfo.type == VT_Unknown) {
                throw CantFindSymbolError(getIntern(var->type->id.name), var->loc);
        }
    }

    TypeInfo VariableInfo::getType() const {
        return typeInfo;
    }

    bool TypeInfo::operator==(const TypeInfo& other) const {
        return (type == other.type && type != VT_Object) || (type == other.type && type == VT_Object && classname == other.classname);
    }

    TypeInfo::TypeInfo(ast::nodes::Type* astType) {
        switch (astType->tt) {
            case AN::TT_Int:
                type = VT_Int;
                break;
            case AN::TT_Array:
                type = VT_IntArray;
                break;
            case AN::TT_Bool:
                type = VT_Boolean;
                break;
            case AN::TT_Object:
                type = VT_Object;
                {
                    auto* symbol = getIntern(astType->id.name);
                    classname = symbol;
                }
                break;
            default:
                type = VT_Unknown;
        }
    }

    std::string TypeInfo::str() const {
        switch (type) {
            case VT_Int:
                return "int";
            case VT_IntArray:
                return "int[]";
            case VT_Boolean:
                return "boolean";
            case VT_Object:
                return classname == nullptr ? "Object" : classname->name;
            default:
                return "Unknown";
        }
    }
}
