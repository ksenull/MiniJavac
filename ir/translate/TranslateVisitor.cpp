//
// Created by ksenull on 5/1/18.
//
#include "TranslateVisitor.h"
#include "NodeConverter.h"
#include "../../common/Exception.h"
#include "../../ast/nodes/Nodes.h"

using BaseException = common::MiniJavacException;

struct CantBuildIrtError : BaseException {
    CantBuildIrtError() : BaseException("Trying to build IR tree from non-method node") {}
};

namespace ir {
    namespace translate {
        namespace IRT = tree;
        namespace AST = AN;
        namespace ST = symboltable;

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Program* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MainClass* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclaration* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ClassDeclarationList* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatementList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclarationStatement* node) const {
            return node->var->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::VariableDeclaration* node) const {
            return new CStmConverter(new IRT::MoveStatement(nullptr, nullptr));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Type* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclarationList* node) const {
            throw CantBuildIrtError();
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::MethodDeclaration* node) const {
            ST::TypeInfo classType(ST::VT_Object, classSymbol);
            ST::VariableInfo thisInfo({}, classType); // TODO save class vars somewhere
            Label* label = ST::getIntern("this");
            frame->AddFormal(label, thisInfo);

            auto* methodLabel = ST::getIntern(node->id.name);
            auto* methodInfo = classInfo->getMethodInfo(methodLabel);

            for (auto&& arg : methodInfo->getArgsList()) {
                frame->AddFormal(arg.first, *arg.second);
            }

            for (auto&& local : methodInfo->getLocalVarsList()) {
                frame->AddLocal(local.first, *local.second);
            }

            if (node->statementList != nullptr && !node->statementList->nodes.empty()) {
                auto* bodySubtree = node->statementList->accept(this);

                if (node->returnExp != nullptr) {
                    auto* returnExpSubtree = node->returnExp->accept(this);

                    return new CStmConverter(new IRT::SeqStatement(bodySubtree->ToStm(), new IRT::MoveStatement(
                            frame->ReturnValue()->getExp(),
                            returnExpSubtree->ToExp())));
                }

                return bodySubtree;
            }
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentDeclarationList* node) const {
            return nullptr;
        }

//        ISubtreeWrapper* IRTranslateVisitor::visit(const AST::INodeList::Iterator& it) {
//            return it->accept(this);
//        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CStatementList* node) const {
            auto&& nodes = node->nodes;

            if (nodes.size() == 1) {
                return nodes[0]->accept(this);
            }
            else {
                return nodes[0]->accept(this);
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NestedStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IfStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::WhileStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::PrintStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::AssignStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayAssignStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentsList* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BinopExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayItemExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayLengthExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CallExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ConstExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BoolExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IdExpression* node) const {
            auto* fp = frame->FramePointer();
            auto* offset = frame->FindLocalOrFormal(ST::getIntern(node->id.name))->getExp();
            auto* addr = new IRT::BinopExpression(fp, IRT::BO_Plus, offset);
            return new CExpConverter(new IRT::MemExpression(addr));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewArrayExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NewObjectExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NotExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::Identifier* node) const {
            return nullptr;
        }

    }
}
