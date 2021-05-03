#include "value.h"

ExpressionNode::~ExpressionNode() {}

TrueNode::TrueNode() {};
int TrueNode::Evaluate() {
    return 1;
}
void TrueNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushValue(1);
}

FalseNode::FalseNode() {};
int FalseNode::Evaluate() {
    return 0;
}
void FalseNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushValue(0);
}

IntegerNode::IntegerNode(int i)
    : value(i) {}
int IntegerNode::Evaluate() {
    return this->value;
}
void IntegerNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushValue(this->value);
}

IdentifierNode::IdentifierNode(std::string label, SymbolTable* table)
    : label(label), table(table) {}

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

void IdentifierNode::CodeEvaluate(InstructionsClass& machineCode) {
    machineCode.PushVariable(this->GetIndex());
}