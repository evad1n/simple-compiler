#if !defined(NODE_H)
#define NODE_H

#include <vector>
#include <string>
#include "symbol.h"

class Node;
class StartNode;
class ProgramNode;
class StatementNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;

class ExpressionNode;
class IntegerNode;
class IdentifierNode;

class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DividesNode;

class LessNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class EqualNode;
class NotEqualNode;


class Node {
public:
    virtual ~Node();
    virtual void Interpret() = 0;
};

class StartNode : public Node {
private:
    ProgramNode* programNode;
public:
    StartNode(ProgramNode* pn);
    ~StartNode();

    void Interpret();
};

class ProgramNode : public Node {
private:
    BlockNode* blockNode;
public:
    ProgramNode(BlockNode* bn);
    ~ProgramNode();

    void Interpret();
};

class StatementNode : public Node {
private:

public:
};

class BlockNode : public StatementNode {
private:
    StatementGroupNode* sgNode;
public:
    BlockNode(StatementGroupNode* sgn);
    ~BlockNode();

    void Interpret();
};

class StatementGroupNode : public Node {
private:
    std::vector<StatementNode*> nodes;
public:
    StatementGroupNode();
    ~StatementGroupNode();

    void Interpret();
    void AddStatement(StatementNode* node);
};


class DeclarationStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    DeclarationStatementNode(IdentifierNode* in);
    ~DeclarationStatementNode();

    void Interpret();
};

class AssignmentStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    IdentifierNode* idNode;
public:
    AssignmentStatementNode(ExpressionNode* en, IdentifierNode* in);
    ~AssignmentStatementNode();

    void Interpret();
};
class CoutStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
public:
    CoutStatementNode(ExpressionNode* en);
    ~CoutStatementNode();

    void Interpret();
};

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

// Mathematical operators

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

// Relational operators

class LessNode : public BinaryOperatorNode {
private:

public:
    LessNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};
class LessEqualNode : public BinaryOperatorNode {
private:

public:
    LessEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};
class GreaterNode : public BinaryOperatorNode {
private:

public:
    GreaterNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};
class GreaterEqualNode : public BinaryOperatorNode {
private:

public:
    GreaterEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};
class EqualNode : public BinaryOperatorNode {
private:

public:
    EqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};
class NotEqualNode : public BinaryOperatorNode {
private:

public:
    NotEqualNode(ExpressionNode* left, ExpressionNode* right);
    int Evaluate();
};



#endif // NODE_H
