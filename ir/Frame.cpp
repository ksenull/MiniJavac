//
// Created by ksenull on 5/2/18.
//
#include "Frame.h"
#include "../common/Exception.h"

using BaseException = common::MiniJavacException;

struct IRFrameAccessError : public BaseException {
    IRFrameAccessError(ir::Label* label) : BaseException("IRFrame access error: can't access var " + label->name) {}
};

namespace ir {

    void Frame::AddFormal(Label* varName, const symboltable::VariableInfo& var) {
        auto* access = new CInRegAccess(RT_Formal, typeSpec->getTypeSize(var.getType().type));
        formals.emplace(std::make_pair(varName, access));
    }

    void Frame::AddLocal(Label* varName, const symboltable::VariableInfo& var) {
        int offset = SP->addr - FP->addr;
        int size = typeSpec->getTypeSize(var.getType().type);
        auto* access = new CInFrameAccess(RT_Local, offset, size);
        SP->addr += size;

        locals.emplace(std::make_pair(varName, access));
    }

    int Frame::FormalsCount() const {
        return 0;
    }

    const IAccess* Frame::Formal(int index) const {
        return nullptr;
    }

    const IAccess* Frame::FindLocalOrFormal(Label* name) const {
        auto&& search = formals.find(name);
        if (search == formals.end()) {
            search = locals.find(name);
            if (search == locals.end()) {
                throw IRFrameAccessError(name);
            }
            return search->second;
        }
        return search->second;
    }

    const IAccess* Frame::ReturnAddress() const {
        return nullptr;
    }

    const IAccess* Frame::ReturnValue() const {
        return new CInRegAccess(RT_ReturnValue, typeSpec->getTypeSize(methodInfo->getReturnType().type));
    }

    void Frame::AddReturnAddress() {

    }

    void Frame::AddReturnType(const symboltable::TypeInfo&) {

    }

    void Frame::PrettyPrint() const {

    }

    tree::IExpression* Frame::FramePointer() const {
        CInRegAccess access(RT_FramePointer, typeSpec->getWordSize(), FP->addr);
        return access.getExp();
    }

    tree::IExpression* Frame::StackPointer() const {
        CInRegAccess access(RT_StackPointer, typeSpec->getWordSize(), SP->addr);
        return access.getExp();
    }

    unsigned Frame::GetWordSize() const {
        return typeSpec->getWordSize();
    }

    tree::IExpression* Frame::ExternalCall(const std::string& functionName, tree::CExpressionList* args) const {
        auto* label = symboltable::getIntern("_" + functionName);
        return new tree::CallExpression(label, args);
    }
}
