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

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CStatementList* node) const {
            auto&& nodes = node->nodes;

            if (nodes.size() == 1) {
                return nodes[0]->accept(this);
            }
            else {
                ISubtreeWrapper* curSeq = nodes[nodes.size() - 1]->accept(this);
                for (int i = nodes.size() - 2; i == 0; i--) {
                    auto* left = nodes[i]->accept(this);
                    if (auto* withCond = dynamic_cast<AST::IfStatement*>(nodes[i])) {
                        Label* done = ST::getIntern("done");
                        curSeq = new CStmConverter(new IRT::SeqStatement(new IRT::LabelStatement(*done), curSeq->ToStm()));
                    }
                    if (auto* withCond = dynamic_cast<AST::WhileStatement*>(nodes[i])) {
                        Label* done = ST::getIntern("done");
                        curSeq = new CStmConverter(new IRT::SeqStatement(new IRT::LabelStatement(*done), curSeq->ToStm()));
                    }
                    curSeq = new CStmConverter(new IRT::SeqStatement(left->ToStm(), curSeq->ToStm()));
                }
                return curSeq;
            }
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::NestedStatement* node) const {
            return node->statementList->accept(this);
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::IfStatement* node) const {
            auto* cond = node->condition->accept(this);
            Label* ifTrue = ST::getIntern("ifTrue");
            Label* ifFalse = ST::getIntern("ifFalse");
            Label* done = ST::getIntern("done");

            auto* ifTrueStm = new IRT::SeqStatement(node->ifStatement->accept(this)->ToStm(), new IRT::JumpStatement(*done));
            auto* ifFalseStm = node->elseStatement->accept(this)->ToStm();
            auto* right = new IRT::SeqStatement(
                    new IRT::SeqStatement(
                            new IRT::LabelStatement(*ifTrue),
                            ifTrueStm
                    ), new IRT::SeqStatement(
                            new IRT::LabelStatement(*ifFalse),
                            ifFalseStm
                    ));
            auto* left = cond->ToConditional(*ifTrue, *ifFalse);
            return new CStmConverter(new IRT::SeqStatement(left, right));

        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::WhileStatement* node) const {
            auto* loopLabel = ST::getIntern("loop");
            auto* bodyLabel = ST::getIntern("body");
            auto* doneLabel = ST::getIntern("done");
            auto* loopPartStm = new IRT::SeqStatement(
                new IRT::LabelStatement(*loopLabel),
                node->condition->accept(this)->ToConditional(*doneLabel, *bodyLabel)
            );
            auto* bodyPartStm = new IRT::SeqStatement(
                    new IRT::LabelStatement(*bodyLabel),
                    node->statement->accept(this)->ToStm()
            );
            return new CStmConverter(new IRT::SeqStatement(loopPartStm, bodyPartStm));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::PrintStatement* node) const {
            Label* print = ST::getIntern("Print");
            auto* args = node->exp->accept(this)->ToStm();
            return new CExpConverter(new IRT::CallExpression(
                    *print,
                    args
                    ));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::AssignStatement* node) const {
            auto* source = node->exp->accept(this);
            auto* target = AST::IdExpression(node->id, {}).accept(this);
            return new CStmConverter(new IRT::MoveStatement(target->ToExp(), source->ToExp()));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayAssignStatement* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArgumentsList* node) const {
            return new CStmConverter(new IRT::SeqStatement(nullptr, nullptr));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::BinopExpression* node) const {
            auto* left = node->left->accept(this)->ToExp();
            auto* right = node->right->accept(this)->ToExp();
            IRT::BinaryOperation op;
            switch (node->type) {
                case AST::BOT_Plus:
                    op = IRT::BO_Plus;
                    break;
                case AST::BOT_Minus:
                    op = IRT::BO_Minus;
                    break;
                case AST::BOT_Multiply:
                    op = IRT::BO_Mul;
                    break;
                case AST::BOT_And:
                    op = IRT::BO_And;
                    break;
                default:
                    return new CCondStmConverter((node->type == AST::BOT_Equal) ? IRT::RO_Eq : IRT::RO_Lt,
                                             left, right);
            }
            return new CExpConverter(new IRT::BinopExpression(left, op, right));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayItemExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ArrayLengthExpression* node) const {
            return nullptr;
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::CallExpression* node) const {
            Label*  obj = ST::getIntern("obj");
            return new CExpConverter(new IRT::CallExpression(*obj, node->args->accept(this)->ToStm()));
        }

        ISubtreeWrapper* IRTranslateVisitor::visit(const AN::ConstExpression* node) const {
            return new CExpConverter(new IRT::ConstExpression(node->value));
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
