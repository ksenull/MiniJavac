#pragma once

#include <fstream>

namespace ast {

        class Program;

        class MainClass;

    class PrintStatement;


    template<typename T>
    class IVisitor {
    public:

#define DECLARE_IVISIT(NODE) virtual T visit(const NODE& node) const = 0;
//
//        DECLARE_IVISIT(Identifier)
        DECLARE_IVISIT(Program)

        DECLARE_IVISIT(MainClass)

        DECLARE_IVISIT(PrintStatement)


#undef DECLARE_IVISIT
    };



    class PrintVisitor : public IVisitor<void> {
    public:
        PrintVisitor() = default;

        explicit PrintVisitor(const std::string& fout);

        ~PrintVisitor() = default;

        void finish();

#define DECLARE_PRINT_VISIT(NODE)  void visit(const NODE& node)  const;

//            DECLARE_PRINT_VISIT(Identifier)

        DECLARE_PRINT_VISIT(Program)

        DECLARE_PRINT_VISIT(MainClass)

        DECLARE_PRINT_VISIT(PrintStatement)

#undef DECLARE_PRINT_VISIT
    private:
        mutable std::ofstream fout;
    };

}
