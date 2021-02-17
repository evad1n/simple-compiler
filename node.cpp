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

IfStatementNode::IfStatementNode(ExpressionNode* en, BlockNode* bn)
    : expNode(en), blockNode(bn) {}
IfStatementNode::~IfStatementNode() {
    delete this->expNode;
    delete this->blockNode;
}
void IfStatementNode::Interpret() {
    if (this->expNode->Evaluate()) {
        this->blockNode->Interpret();
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

BitwiseAndNode::BitwiseAndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int BitwiseAndNode::Evaluate() {
    return this->left->Evaluate() & this->right->Evaluate();
}

BitwiseOrNode::BitwiseOrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int BitwiseOrNode::Evaluate() {
    return this->left->Evaluate() | this->right->Evaluate();
}

AndNode::AndNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int AndNode::Evaluate() {
    return this->left->Evaluate() && this->right->Evaluate();
}

OrNode::OrNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}

int OrNode::Evaluate() {
    return this->left->Evaluate() || this->right->Evaluate();
}