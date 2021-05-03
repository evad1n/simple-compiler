#if !defined(VALUE_H)
#define VALUE_H

#include <string>
#include "../symbol.h"
#include "../machine-code/instructions.h"

class ExpressionNode;
class IntegerNode;
class IdentifierNode;

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
    virtual void CodeEvaluate(InstructionsClass& machineCode) = 0;
};

class TrueNode : public ExpressionNode {
private:
public:
    TrueNode();
    // Return the integer value
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class FalseNode : public ExpressionNode {
private:
public:
    FalseNode();
    // Return the integer value
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class IntegerNode : public ExpressionNode {
private:
    int value;
public:
    IntegerNode(int i);
    // Return the integer value
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

class IdentifierNode : public ExpressionNode {
private:
    std::string label;
    SymbolTable* table;
public:
    IdentifierNode(std::string label, SymbolTable* table);
    ~IdentifierNode();

    void DeclareVariable();
    void SetValue(int v);
    // Index into symbol table
    int GetIndex();
    // Return the integer value of the identifier
    int Evaluate();
    void CodeEvaluate(InstructionsClass& machineCode);
};

#endif // VALUE_H
