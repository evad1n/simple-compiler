#include "value.h"

ExpressionNode::~ExpressionNode() {}


IntegerNode::IntegerNode(int i)
    : value(i) {}

int IntegerNode::Evaluate() {
    return this->value;
}

IdentifierNode::IdentifierNode(std::string label, SymbolTable* symTable)
    : label(label), table(symTable) {}

IdentifierNode::~IdentifierNode() {}

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