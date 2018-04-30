#pragma once

#include "Symbol.h"
#include "../ast/nodes/Nodes.h"


namespace symboltable {
    enum VariableType {
        VT_Int,
        VT_IntArray,
        VT_Boolean,
        VT_Object,
        VT_Void,
        VT_Unknown
    };

    struct TypeInfo {
        TypeInfo(VariableType type, Symbol* symbol) : type(type), classname(symbol) {}
        TypeInfo(VariableType type) : TypeInfo(type, nullptr) {}
        TypeInfo() : TypeInfo(VT_Unknown, nullptr) {}

        explicit TypeInfo(ast::nodes::Type* astType);
        TypeInfo(const TypeInfo& other) = default;
        TypeInfo& operator=(const TypeInfo& other) = default;
        
        bool operator==(const TypeInfo& other) const;
        
        bool isInt() { return type == VT_Int; }
        bool isBool() { return type == VT_Boolean; }
        
        std::string str() const;
        
        VariableType type;
        Symbol* classname;
    };
    
    class VariableInfo : public IInfo {
    public:
        explicit VariableInfo(const common::Location& loc) : IInfo(loc) {}
        
        VariableInfo(const common::Location& loc, const TypeInfo& type) : IInfo(loc), typeInfo(type) {} // for ir

        void BuildFromAst(ast::nodes::VariableDeclaration* var);

        TypeInfo getType() const;
    private:
        TypeInfo typeInfo;
    };
}