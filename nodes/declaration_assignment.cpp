#include "declaration_assignment.h"

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in)
    : IDNode(in) {}
DeclarationStatementNode::~DeclarationStatementNode() {
    delete this->IDNode;
}
void DeclarationStatementNode::Interpret() {
    this->IDNode->DeclareVariable();
}

DeclarationAssignmentStatementNode::DeclarationAssignmentStatementNode(IdentifierNode* in, ExpressionNode* en)
    : DeclarationStatementNode(in), expNode(en) {}
DeclarationAssignmentStatementNode::~DeclarationAssignmentStatementNode() {
    delete this->expNode;
}
void DeclarationAssignmentStatementNode::Interpret() {
    this->IDNode->DeclareVariable();
    int val = this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en)
    : IDNode(in), expNode(en) {}
AssignmentStatementNode::~AssignmentStatementNode() {
    delete this->IDNode;
    delete this->expNode;
}
void AssignmentStatementNode::Interpret() {
    int val = this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

PlusEqualsStatementNode::PlusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : IDNode(in), expNode(en) {}
PlusEqualsStatementNode::~PlusEqualsStatementNode() {
    delete this->IDNode;
    delete this->expNode;
}
void PlusEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() + this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

MinusEqualsStatementNode::MinusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : IDNode(in), expNode(en) {}
MinusEqualsStatementNode::~MinusEqualsStatementNode() {
    delete this->IDNode;
    delete this->expNode;
}
void MinusEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() - this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

MultiplyEqualsStatementNode::MultiplyEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : IDNode(in), expNode(en) {}
MultiplyEqualsStatementNode::~MultiplyEqualsStatementNode() {
    delete this->IDNode;
    delete this->expNode;
}
void MultiplyEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() * this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

DivideEqualsStatementNode::DivideEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : IDNode(in), expNode(en) {}
DivideEqualsStatementNode::~DivideEqualsStatementNode() {
    delete this->IDNode;
    delete this->expNode;
}
void DivideEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() / this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

IncrementStatementNode::IncrementStatementNode(IdentifierNode* in)
    : IDNode(in) {}
IncrementStatementNode::~IncrementStatementNode() {
    delete this->IDNode;
}
void IncrementStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() + 1;
    this->IDNode->SetValue(val);
}

DecrementStatementNode::DecrementStatementNode(IdentifierNode* in)
    : IDNode(in) {}
DecrementStatementNode::~DecrementStatementNode() {
    delete this->IDNode;
}
void DecrementStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() - 1;
    this->IDNode->SetValue(val);
}