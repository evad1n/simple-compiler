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
    std::vector<SymbolTable*> scopes;
    int nearest;
public:
    IdentifierNode(std::string label, std::vector<SymbolTable*> scopes);
    ~IdentifierNode();

    // Returns the nearest symbol table scope
    SymbolTable* GetNearestScope();

    void DeclareVariable();
    void SetValue(int v);
    // Index into symbol table
    int GetIndex();
    // Return the integer value of the identifier
    int Evaluate();
};

#endif // VALUE_H
