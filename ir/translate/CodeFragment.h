#pragma once

#include <utility>
#include "../Frame.h"


namespace ir {
    namespace tree {
        class IStatement;
    }

    namespace translate {
        class CCodeFragment {
        public:
            CCodeFragment(Frame* _frame, tree::IStatement* _body, std::string _className, std::string _methodName) :
                    frame(_frame), body(_body), next(nullptr), className(std::move(_className)), methodName(
                    std::move(_methodName)){};
            CCodeFragment(const CCodeFragment& ) = default;
            ~CCodeFragment() = default;

            void SetNext(CCodeFragment* _next) {
                next = _next;
            }
            CCodeFragment* GetNext() const { return next; }
            tree::IStatement* const GetBody() const { return body; }
            IFrame* GetFrame() const { return frame; };
            std::string GetName() const { return className + "@" + methodName; }
        private:
            IFrame* frame;
            tree::IStatement* body;
            CCodeFragment* next;
            std::string className;
            std::string methodName;
        };
    }
}