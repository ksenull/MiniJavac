#pragma once

namespace ast {

    namespace nodes {
        class Program;
        class MainClass;
        class Identifier;
        class Assign;
        class IfElse;
        class While;
        class Print;
        class SetItem;

        class And;
        class Less;
        class Plus;
        class Minus;
        class Mult;
    }

    template <typename T>
    class IVisitor {
    public:

#define DECLARE_IVISIT(NODE) virtual T visit(const nodes::NODE* node) const = 0;

        DECLARE_IVISIT(Program)
        DECLARE_IVISIT(MainClass)
        DECLARE_IVISIT(Identifier)
        DECLARE_IVISIT(Assign)
        DECLARE_IVISIT(IfElse)
        DECLARE_IVISIT(While)
        DECLARE_IVISIT(Print)
        DECLARE_IVISIT(SetItem)

        DECLARE_IVISIT(And)
        DECLARE_IVISIT(Less)
        DECLARE_IVISIT(Plus)
        DECLARE_IVISIT(Minus)
        DECLARE_IVISIT(Mult)

#undef DECLARE_IVISIT
    };
}
