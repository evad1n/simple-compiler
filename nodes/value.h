#if !defined(VALUE_H)
#define VALUE_H

#include <string>
#include "../symbol.h"

class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
};


class IntegerNode : public ExpressionNode {
private:
    int value;
public:
    IntegerNode(int i);
    // Return the integer value
    int Evaluate();
};

class IdentifierNode : public ExpressionNode {
private:
    std::string label;
    SymbolTable* table;
public:
    IdentifierNode(std::string label, SymbolTable* symTable);
    ~IdentifierNode();

    void DeclareVariable();
    void SetValue(int v);
    // Index into symbol table
    int GetIndex();
    // Return the integer value of the identifier
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

#endif // VALUE_H
