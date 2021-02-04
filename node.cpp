#include "node.h"

Node::~Node() {}

StartNode::StartNode(ProgramNode* pn)
    : programNode(pn) {}

StartNode::~StartNode() {
    delete this->programNode;
}

ProgramNode::ProgramNode(BlockNode* bn)
    : blockNode(bn) {}

ProgramNode::~ProgramNode() {
    delete this->blockNode;
}

BlockNode::BlockNode(StatementGroupNode* sgn)
    : sgNode(sgn) {}

BlockNode::~BlockNode() {
    delete this->sgNode;
}

StatementGroupNode::StatementGroupNode()
    : nodes(std::vector<StatementNode*>{}) {}

StatementGroupNode::~StatementGroupNode() {
    for (auto n : this->nodes) {
        delete n;
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

AssignmentStatementNode::AssignmentStatementNode(ExpressionNode* en, IdentifierNode* in)
    : expNode(en), idNode(in) {}

AssignmentStatementNode::~AssignmentStatementNode() {
    delete this->expNode;
    delete this->idNode;
}

CoutStatementNode::CoutStatementNode(ExpressionNode* en)
    : expNode(en) {}

CoutStatementNode::~CoutStatementNode() {
    delete this->expNode;
}

ExpressionNode::~ExpressionNode() {}


IntegerNode::IntegerNode(int i)
    : value(i) {}

int IntegerNode::Evaluate() {
    return this->value;
}

IdentifierNode::IdentifierNode(SymbolTable* symTable)
    : table(symTable) {}

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

PlusNode::PlusNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int PlusNode::Evaluate() {
    return this->left->Evaluate() + this->right->Evaluate();
}