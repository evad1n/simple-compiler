#if !defined(NODE_H)
#define NODE_H

#include <vector>
#include <string>
#include "symbol.h"

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;

class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class BinaryOperatorNode;
class PlusNode;

class Node {
public:
    virtual ~Node();
};

class StartNode : public Node {
private:
    ProgramNode* programNode;
public:
    StartNode(ProgramNode* pn);
    ~StartNode();
};

class ProgramNode : public Node {
private:
    BlockNode* blockNode;
public:
    ProgramNode(BlockNode* bn);
    ~ProgramNode();
};

class BlockNode : public Node {
private:
    StatementGroupNode* sgNode;
public:
    BlockNode(StatementGroupNode* sgn);
    ~BlockNode();
};

class StatementGroupNode : public Node {
private:
    std::vector<StatementNode*> nodes;
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void AddStatement(StatementNode* node);
};

class StatementNode : public Node {
private:

public:
};

class DeclarationStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    DeclarationStatementNode(IdentifierNode* in);
    ~DeclarationStatementNode();
};

class AssignmentStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    IdentifierNode* idNode;
public:
    AssignmentStatementNode(ExpressionNode* en, IdentifierNode* in);
    ~AssignmentStatementNode();
};

class ExpressionNode {
public:
    virtual ~ExpressionNode();
    virtual int Evaluate() = 0;
};

class CoutStatementNode : public Node {
private:
    ExpressionNode* expNode;
public:
    CoutStatementNode(ExpressionNode* en);
    ~CoutStatementNode();
};

class IntegerNode : public ExpressionNode {
private:
    int value;
public:
    IntegerNode(int i);
    int Evaluate();
};

class IdentifierNode : public ExpressionNode {
private:
    std::string label;
    SymbolTable* table;
public:
    IdentifierNode(SymbolTable* symTable);
    ~IdentifierNode();

    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
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

class PlusNode : public BinaryOperatorNode {
private:

public:
    PlusNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};



#endif // NODE_H
