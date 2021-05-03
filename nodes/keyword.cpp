#include <iostream>
#include "keyword.h"

IfElseStatementNode::IfElseStatementNode(ExpressionNode* ifExp, StatementNode* ifBranch, StatementNode* elseBranch)
    : ifExp(ifExp), ifBranch(ifBranch), elseBranch(elseBranch) {}
IfElseStatementNode::~IfElseStatementNode() {
    delete this->ifExp;
    delete this->ifBranch;
    delete this->elseBranch;
}
void IfElseStatementNode::Interpret() {
    if (this->ifExp->Evaluate()) {
        this->ifBranch->Interpret();
    } else if (this->elseBranch != NULL) {
        this->elseBranch->Interpret();
    }
}
void IfElseStatementNode::Code(InstructionsClass& machineCode) {
    this->ifExp->CodeEvaluate(machineCode);
    unsigned char* insertAddress = machineCode.SkipIfZeroStack();
    unsigned char* address1 = machineCode.GetAddress();
    this->ifBranch->Code(machineCode);
    unsigned char* address2 = machineCode.GetAddress();
    machineCode.SetOffset(insertAddress, (int)(address2 - address1));
}

WhileStatementNode::WhileStatementNode(ExpressionNode* en, BlockNode* bn)
    : expNode(en), blockNode(bn) {}
WhileStatementNode::~WhileStatementNode() {
    delete this->expNode;
    delete this->blockNode;
}
void WhileStatementNode::Interpret() {
    while (this->expNode->Evaluate()) {
        this->blockNode->Interpret();
    }
}
void WhileStatementNode::Code(InstructionsClass& machineCode) {
    unsigned char* address1 = machineCode.GetAddress();
    this->expNode->CodeEvaluate(machineCode);
    unsigned char* insertAddressSkip = machineCode.SkipIfZeroStack();
    unsigned char* address2 = machineCode.GetAddress();
    this->blockNode->Code(machineCode);
    unsigned char* insertAddressJump = machineCode.Jump();
    unsigned char* address3 = machineCode.GetAddress();
    machineCode.SetOffset(insertAddressSkip, (int)(address3 - address2));
    machineCode.SetOffset(insertAddressJump, (int)(address1 - address3));
}


ForStatementNode::ForStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn,
    SymbolTable* table)
    : initializer(initializer),
    comparison(comparison),
    incrementer(incrementer),
    blockNode(bn),
    table(table) {}
ForStatementNode::~ForStatementNode() {
    delete this->initializer;
    delete this->comparison;
    delete this->incrementer;
    delete this->blockNode;
}
void ForStatementNode::Interpret() {
    this->table->NewScope();
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        this->blockNode->Interpret();
        this->incrementer->Interpret();
    }
    this->table->LeaveScope();
}
void ForStatementNode::Code(InstructionsClass& machineCode) {

}

ForeStatementNode::ForeStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn,
    SymbolTable* table)
    : ForStatementNode(initializer, comparison, incrementer, bn, table) {}
void ForeStatementNode::Interpret() {
    this->table->NewScope();
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        for (int i = 0; i < 4; i++) {
            this->blockNode->Interpret();
        }
        this->incrementer->Interpret();
    }
    this->table->LeaveScope();
}
void ForeStatementNode::Code(InstructionsClass& machineCode) {

}


CoutStatementNode::CoutStatementNode(std::vector<ExpressionNode*> ens)
    : expNodes(ens) {}
CoutStatementNode::~CoutStatementNode() {
    for (auto e : this->expNodes) {
        delete e;
    }
}
void CoutStatementNode::Interpret() {
    for (auto e : this->expNodes) {
        if (e == NULL) {
            std::cout << std::endl;
        } else {
            std::cout << e->Evaluate();
        }
    }
}
void CoutStatementNode::Code(InstructionsClass& machineCode) {
    for (auto e : this->expNodes) {
        if (e == NULL) {
            machineCode.WriteEndl();
        } else {
            e->CodeEvaluate(machineCode);
            machineCode.PopAndWrite();
        }
    }
}

CinStatementNode::CinStatementNode(std::vector<IdentifierNode*> vars)
    : variables(vars) {}
CinStatementNode::~CinStatementNode() {
    for (auto e : this->variables) {
        delete e;
    }
}
void CinStatementNode::Interpret() {
    for (auto e : this->variables) {
        int var;
        std::cout << ">> ";
        std::cin >> var;
        e->SetValue(var);
    }
}
void CinStatementNode::Code(InstructionsClass& machineCode) {
    for (auto e : this->variables) {
        machineCode.ReadAndStoreVariable(e->GetIndex());
    }
}
