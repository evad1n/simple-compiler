#include "operator.h"

TernaryOperatorNode::TernaryOperatorNode(ExpressionNode* first, ExpressionNode* second, ExpressionNode* third)
    : first(first), second(second), third(third) {}
TernaryOperatorNode::~TernaryOperatorNode() {
    delete first;
    delete second;
    delete third;
}
int TernaryOperatorNode::Evaluate() {
    return first->Evaluate() ? second->Evaluate() : third->Evaluate();
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right)
    : left(left), right(right) {}
BinaryOperatorNode::~BinaryOperatorNode() {
    delete left;
    delete right;
}

UnaryOperatorNode::UnaryOperatorNode(ExpressionNode* val)
    : val(val) {}
UnaryOperatorNode::~UnaryOperatorNode() {
    delete val;
}