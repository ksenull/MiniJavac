#pragma once

#include "../Frame.h"


namespace ir {
    namespace tree {
        class IStatement;
    }

    namespace translate {
        class CCodeFragment {
        public:
            CCodeFragment(Frame* _frame, tree::IStatement* _body) : frame(_frame), body(_body), next(nullptr) {};
            CCodeFragment(const CCodeFragment& ) = default;
            ~CCodeFragment() = default;

            void SetNext(CCodeFragment* _next) {
                next = _next;
            }
            CCodeFragment* GetNext() const { return next; }
            tree::IStatement* const GetBody() const { return body; }
            IFrame* GetFrame() const { return frame; };
        private:
            IFrame* frame;
            tree::IStatement* body;
            CCodeFragment* next;
        };
    }
}