#include <iostream>
#include "node.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* pn)
    : programNode(pn) {}
StartNode::~StartNode() {
    delete this->programNode;
}
void StartNode::Interpret() {
    this->programNode->Interpret();
}

ProgramNode::ProgramNode(BlockNode* bn)
    : blockNode(bn) {}
ProgramNode::~ProgramNode() {
    delete this->blockNode;
}
void ProgramNode::Interpret() {
    this->blockNode->Interpret();
}

BlockNode::BlockNode(StatementGroupNode* sgn)
    : sgNode(sgn) {}
BlockNode::~BlockNode() {
    delete this->sgNode;
}
void BlockNode::Interpret() {
    this->sgNode->Interpret();
}

StatementGroupNode::StatementGroupNode()
    : nodes(std::vector<StatementNode*>{}) {}
StatementGroupNode::~StatementGroupNode() {
    for (auto n : this->nodes) {
        delete n;
    }
}
void StatementGroupNode::Interpret() {
    for (auto n : this->nodes) {
        n->Interpret();
    }
}
void StatementGroupNode::AddStatement(StatementNode* node) {
    this->nodes.push_back(node);
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in)
    : IDNode(in) {}
DeclarationStatementNode::~DeclarationStatementNode() {
    delete this->IDNode;
}
void DeclarationStatementNode::Interpret() {
    this->IDNode->DeclareVariable();
}

AssignmentStatementNode::AssignmentStatementNode(ExpressionNode* en, IdentifierNode* in)
    : expNode(en), idNode(in) {}
AssignmentStatementNode::~AssignmentStatementNode() {
    delete this->expNode;
    delete this->idNode;
}
void AssignmentStatementNode::Interpret() {
    int val = this->expNode->Evaluate();
    this->idNode->SetValue(val);
}

CoutStatementNode::CoutStatementNode(ExpressionNode* en)
    : expNode(en) {}
CoutStatementNode::~CoutStatementNode() {
    delete this->expNode;
}
void CoutStatementNode::Interpret() {
    int val = this->expNode->Evaluate();
    std::cout << val << std::endl;
}

ExpressionNode::~ExpressionNode() {}


IntegerNode::IntegerNode(int i)
    : value(i) {}

int IntegerNode::Evaluate() {
    return this->value;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTable* symTable)
    : label(label), table(symTable) {}

IdentifierNode::~IdentifierNode() {
    delete this->table;
}

void IdentifierNode::DeclareVariable() {
    this->table->AddEntry(this->label);
}

void IdentifierNode::SetValue(int v) {
    this->table->SetValue(this->label, v);
}

int IdentifierNode::GetIndex() {
    return this->table->GetIndex(this->label);
}

int IdentifierNode::Evaluate() {
    return this->table->GetValue(this->label);
}


BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
    : left(left), right(right) {}
BinaryOperatorNode::~BinaryOperatorNode() {
    delete left;
    delete right;
}

// Mathematical operators

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int PlusNode::Evaluate() {
    return this->left->Evaluate() + this->right->Evaluate();
}

MinusNode::MinusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int MinusNode::Evaluate() {
    return this->left->Evaluate() - this->right->Evaluate();
}

TimesNode::TimesNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int TimesNode::Evaluate() {
    return this->left->Evaluate() * this->right->Evaluate();
}

DivideNode::DivideNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int DivideNode::Evaluate() {
    return this->left->Evaluate() / this->right->Evaluate();
}

// Relational operators

LessNode::LessNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int LessNode::Evaluate() {
    return this->left->Evaluate() < this->right->Evaluate();
}

LessEqualNode::LessEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int LessEqualNode::Evaluate() {
    return this->left->Evaluate() <= this->right->Evaluate();
}

GreaterNode::GreaterNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int GreaterNode::Evaluate() {
    return this->left->Evaluate() > this->right->Evaluate();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int GreaterEqualNode::Evaluate() {
    return this->left->Evaluate() >= this->right->Evaluate();
}

EqualNode::EqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int EqualNode::Evaluate() {
    return this->left->Evaluate() == this->right->Evaluate();
}

NotEqualNode::NotEqualNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int NotEqualNode::Evaluate() {
    return this->left->Evaluate() != this->right->Evaluate();
}