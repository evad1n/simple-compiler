#include <cmath>
#include "math.h"

// =========================================================
// Mathematical operators
// =========================================================


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

ExponentNode::ExponentNode(ExpressionNode* left, ExpressionNode* right)
    : BinaryOperatorNode(left, right) {}
int ExponentNode::Evaluate() {
    return pow(this->left->Evaluate(), this->right->Evaluate());
}

NegativeNode::NegativeNode(ExpressionNode* val)
    : UnaryOperatorNode(val) {}
int NegativeNode::Evaluate() {
    return -1 * this->val->Evaluate();
}