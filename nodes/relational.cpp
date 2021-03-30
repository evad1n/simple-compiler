#include "relational.h"

// =========================================================
// Relational operators
// =========================================================


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


// =========================================================
// AND/OR
// =========================================================


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