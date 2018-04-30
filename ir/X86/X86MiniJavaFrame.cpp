//
// Created by ksenull on 4/30/18.
//
#include "X86MiniJavaFrame.h"

namespace ir {

    void CX86MiniJavaFrame::AddFormal(ST::Symbol* varName, const ST::VariableInfo& var) {
        auto* inRegAccess = new CInRegAccess(RT_Formal, 0, typeSpec->getTypeSize(var.getType().type));
        formalsList.emplace_back(inRegAccess);
        formals.emplace(std::make_pair(varName, inRegAccess));
    }

    void CX86MiniJavaFrame::AddLocal(ST::Symbol* varName, const ST::VariableInfo& var) {
        auto* inFrameAccess = new CInFrameAccess(RT_Local, 0, typeSpec->getTypeSize(var.getType().type));
        locals.emplace(std::make_pair(varName, inFrameAccess));
    }

    int CX86MiniJavaFrame::FormalsCount() const {
        return formalsList.size();
    }

    const IAccess* CX86MiniJavaFrame::Formal(int index) const {
        return formalsList.at(index);
    }

    const IAccess* CX86MiniJavaFrame::FindLocalOrFormal(const ST::Symbol* name) const {
        auto&& search = locals.find(name);
        if (search == locals.end()) {
            search = formals.find(name);
            if (search == formals.end()) {
                return nullptr;
            }
        }
        return search->second;
    }

    int CX86MiniJavaFrame::FramePointer() const {
        return framePointer;
    }

    int CX86MiniJavaFrame::StackPointer() const {
        return stackPointer;
    }

    const IAccess* CX86MiniJavaFrame::ReturnAddress() const {
        return returnAddress;
    }

    const IAccess* CX86MiniJavaFrame::ReturnValue() const {
        return returnValue;
    }

    void CX86MiniJavaFrame::AddReturnAddress() {
        auto* inRegAccess = new CInRegAccess(RT_ReturnAddress, 0, typeSpec->getRefSize());
        returnAddress = inRegAccess;
    }

    void CX86MiniJavaFrame::AddReturnType(const ST::TypeInfo& info) {
        auto* inFrameAccess = new CInFrameAccess(RT_ReturnValue, 0, typeSpec->getTypeSize(info.type));
        returnValue = inFrameAccess;
    }

    void CX86MiniJavaFrame::PrettyPrint() const {
        std::cout << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << returnAddress->str() << std::endl;
        for (auto&& formal : formals) {
            std::cout << formal.first->name << "#" << formal.second->str() << std::endl;
        }
        for (auto&& local : formals) {
            std::cout << local.first->name << "#" << local.second->str() << std::endl;
        }
        if (returnValue) {
            std::cout << returnValue << std::endl;
        }
        std::cout << "------------------------" << std::endl;
    }
}