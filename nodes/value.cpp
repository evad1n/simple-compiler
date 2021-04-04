#include "value.h"

ExpressionNode::~ExpressionNode() {}


IntegerNode::IntegerNode(int i)
    : value(i) {}

int IntegerNode::Evaluate() {
    return this->value;
}

IdentifierNode::IdentifierNode(std::string label, std::vector<SymbolTable*> scopes)
    : label(label), scopes(scopes), nearest(scopes.size() - 1) {}

IdentifierNode::~IdentifierNode() {}

SymbolTable* IdentifierNode::GetNearestScope() {
    int cur = this->scopes.size() - 1;
    while (!this->scopes[cur]->Exists(this->label)) {
        cur--;
        if (cur <= 0) {
            cur = 0;
            break;
        }
    }
    return this->scopes[cur];
}

void IdentifierNode::DeclareVariable() {
    this->scopes[this->nearest]->AddEntry(this->label);
}

void IdentifierNode::SetValue(int v) {
    this->GetNearestScope()->SetValue(this->label, v);
}

int IdentifierNode::GetIndex() {
    return this->GetNearestScope()->GetIndex(this->label);
}

int IdentifierNode::Evaluate() {
    return this->GetNearestScope()->GetValue(this->label);
}