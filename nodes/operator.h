#if !defined(OPERATOR_H)
#define OPERATOR_H

#include "value.h"

class TernaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode* first;
    ExpressionNode* second;
    ExpressionNode* third;
public:
    TernaryOperatorNode(ExpressionNode* first, ExpressionNode* second, ExpressionNode* third);
    ~TernaryOperatorNode();

    int Evaluate();
};

class BinaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode* left;
    ExpressionNode* right;
public:
    BinaryOperatorNode(ExpressionNode* left, ExpressionNode* right);
    ~BinaryOperatorNode();
};

class UnaryOperatorNode : public ExpressionNode {
protected:
    ExpressionNode* val;
public:
    UnaryOperatorNode(ExpressionNode* val);
    ~UnaryOperatorNode();
};

#endif // OPERATOR_H
