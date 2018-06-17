#pragma once

#include "../Codegen.h"


namespace codegen {
    namespace fasm {
        class IOperand;

        class CCodegen : public ICodegen {
        public:
            using ICodegen::Gen;
            CInstructionList Gen(ir::IFrame* _frame, ir::tree::IStatement* stm) override;
        private:
            IOperand* munchExp(ir::tree::IExpression* exp);
            void munchStm(ir::tree::IStatement* stm);

            ir::IFrame* frame;
            CInstructionList result;
        };

    }
}