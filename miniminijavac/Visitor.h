#pragma once

#include <fstream>

namespace ast {

        class Program;

        class MainClass;

    class PrintStatement;

    class ReturnStatement;

    class CStatementList;


    template<typename T>
    class IVisitor {
    public:

#define DECLARE_IVISIT(NODE) virtual T visit(const NODE* node) const = 0;
//
//        DECLARE_IVISIT(Identifier)
        DECLARE_IVISIT(Program)

        DECLARE_IVISIT(MainClass)

        DECLARE_IVISIT(PrintStatement)

        DECLARE_IVISIT(ReturnStatement)

        DECLARE_IVISIT(CStatementList)


#undef DECLARE_IVISIT
    };



    class PrintVisitor : public IVisitor<void> {
    public:
        PrintVisitor() = default;

        explicit PrintVisitor(const std::string& fout);

        ~PrintVisitor() = default;

        void finish();

#define DECLARE_PRINT_VISIT(NODE)  void visit(const NODE* node)  const;

//            DECLARE_PRINT_VISIT(Identifier)

        DECLARE_PRINT_VISIT(Program)

        DECLARE_PRINT_VISIT(MainClass)

        DECLARE_PRINT_VISIT(PrintStatement)

        DECLARE_PRINT_VISIT(ReturnStatement)

        DECLARE_PRINT_VISIT(CStatementList)

#undef DECLARE_PRINT_VISIT
    private:
        mutable std::ofstream fout;
    };

}
