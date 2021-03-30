#if !defined(MATH_H)
#define MATH_H

#include "value.h"

class PlusNode;
class MinusNode;
class TimesNode;
class DividesNode;
class ExponentNode;

class PlusNode : public BinaryOperatorNode {
private:

public:
    PlusNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};

class MinusNode : public BinaryOperatorNode {
private:

public:
    MinusNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};

class TimesNode : public BinaryOperatorNode {
private:

public:
    TimesNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};

class DivideNode : public BinaryOperatorNode {
private:

public:
    DivideNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};

class ExponentNode : public BinaryOperatorNode {
private:

public:
    ExponentNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};

#endif // MATH_H
