#include "declaration_assignment.h"

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in)
    : IDNode(in) {}
DeclarationStatementNode::~DeclarationStatementNode() {
    delete this->IDNode;
}
void DeclarationStatementNode::Interpret() {
    this->IDNode->DeclareVariable();
}
void DeclarationStatementNode::Code(InstructionsClass& machineCode) {
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
void DeclarationAssignmentStatementNode::Code(InstructionsClass& machineCode) {
    this->IDNode->DeclareVariable();
    this->expNode->CodeEvaluate(machineCode);
    int index = this->IDNode->GetIndex();
    machineCode.PopAndStore(index);
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
void AssignmentStatementNode::Code(InstructionsClass& machineCode) {
    this->expNode->CodeEvaluate(machineCode);
    int index = this->IDNode->GetIndex();
    machineCode.PopAndStore(index);
}

PlusEqualsStatementNode::PlusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void PlusEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() + this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

MinusEqualsStatementNode::MinusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void MinusEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() - this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

MultiplyEqualsStatementNode::MultiplyEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
void MultiplyEqualsStatementNode::Interpret() {
    int val = this->IDNode->Evaluate() * this->expNode->Evaluate();
    this->IDNode->SetValue(val);
}

DivideEqualsStatementNode::DivideEqualsStatementNode(IdentifierNode* in, ExpressionNode* en)
    : AssignmentStatementNode(in, en) {}
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
void IncrementStatementNode::Code(InstructionsClass& machineCode) {
    this->IDNode->CodeEvaluate(machineCode);
    machineCode.PushValue(1);
    machineCode.PopPopAddPush();
    int index = this->IDNode->GetIndex();
    machineCode.PopAndStore(index);
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
void DecrementStatementNode::Code(InstructionsClass& machineCode) {
    this->IDNode->CodeEvaluate(machineCode);
    machineCode.PushValue(1);
    machineCode.PopPopSubPush();
    int index = this->IDNode->GetIndex();
    machineCode.PopAndStore(index);
}