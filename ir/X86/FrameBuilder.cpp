//
// Created by ksenull on 4/30/18.
//
#include "FrameBuilder.h"

#include "X86MiniJavaFrame.h"

namespace ir {
    using TypeInfo = ST::TypeInfo;

    IFrame* FrameBuilder::BuildFromST(Symbol* caller, ST::Symbol* classSymbol, ST::Symbol* methodSymbol) {
        IFrame* frame = new CX86MiniJavaFrame(new X86MiniJavaTypeSpec(), 0, 0); // TODO make template

        auto* classInfo = table->getClassInfo(classSymbol);

        ST::TypeInfo callerType(ST::VT_Object, classSymbol);
        ST::VariableInfo callerInfo(classInfo->loc, callerType);
        frame->AddFormal(caller, callerInfo);

        auto* methodInfo = classInfo->getMethodInfo(methodSymbol);

        auto args = methodInfo->getArgsList();
        for (auto&& arg : args) {
            frame->AddFormal(arg.first, *arg.second);
        }
        auto locals = methodInfo->getLocalVarsList();
        for(auto&& loc : locals) {
            frame->AddLocal(loc.first, *loc.second);
        }
        frame->AddReturnAddress();
        if (methodInfo->getReturnType().type != ST::VT_Void) {
            frame->AddReturnType(methodInfo->getReturnType());
        }
        return frame;
    }

    IFrame* FrameBuilder::BuildFromMain(AN::MainClass* mainClass) {
        auto* classSymbol = ST::getIntern(mainClass->name.name);
        auto method = ST::getIntern("main");
        Symbol* caller = ST::getIntern("");
        return BuildFromST(caller, classSymbol, method);
    }
}
