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

ForStatementNode::ForStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn)
    : initializer(initializer),
    comparison(comparison),
    incrementer(incrementer),
    blockNode(bn) {}
ForStatementNode::~ForStatementNode() {
    delete this->initializer;
    delete this->comparison;
    delete this->incrementer;
    delete this->blockNode;
}
void ForStatementNode::Interpret() {
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        this->blockNode->Interpret();
        this->incrementer->Interpret();
    }
}

ForeStatementNode::ForeStatementNode(
    StatementNode* initializer,
    ExpressionNode* comparison,
    StatementNode* incrementer,
    BlockNode* bn)
    : initializer(initializer),
    comparison(comparison),
    incrementer(incrementer),
    blockNode(bn) {}
ForeStatementNode::~ForeStatementNode() {
    delete this->initializer;
    delete this->comparison;
    delete this->incrementer;
    delete this->blockNode;
}
void ForeStatementNode::Interpret() {
    this->initializer->Interpret();
    while (this->comparison->Evaluate()) {
        for (int i = 0; i < 4; i++) {
            this->blockNode->Interpret();
        }
        this->incrementer->Interpret();
    }
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