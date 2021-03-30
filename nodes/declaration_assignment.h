#if !defined(DECLARATION_ASSIGNMENT_H)
#define DECLARATION_ASSIGNMENT_H

#include "base.h"
#include "value.h"


class DeclarationStatementNode;
class DeclarationAssignmentStatementNode;
class AssignmentStatementNode;

class PlusEqualsStatementNode;
class MinusEqualsStatementNode;
class MultiplyEqualsStatementNode;
class DivideEqualsStatementNode;

class IncrementStatementNode;
class DecrementStatementNode;

class DeclarationStatementNode : public StatementNode {
protected:
    IdentifierNode* IDNode;
public:
    DeclarationStatementNode(IdentifierNode* in);
    ~DeclarationStatementNode();

    void Interpret();
};

class DeclarationAssignmentStatementNode : public DeclarationStatementNode {
private:
    ExpressionNode* expNode;
public:
    DeclarationAssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~DeclarationAssignmentStatementNode();

    void Interpret();
};

class AssignmentStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    AssignmentStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~AssignmentStatementNode();

    void Interpret();
};

class PlusEqualsStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    PlusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~PlusEqualsStatementNode();

    void Interpret();
};

class MinusEqualsStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    MinusEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~MinusEqualsStatementNode();

    void Interpret();
};

class MultiplyEqualsStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    MultiplyEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~MultiplyEqualsStatementNode();

    void Interpret();
};

class DivideEqualsStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
    ExpressionNode* expNode;
public:
    DivideEqualsStatementNode(IdentifierNode* in, ExpressionNode* en);
    ~DivideEqualsStatementNode();

    void Interpret();
};

class IncrementStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    IncrementStatementNode(IdentifierNode* in);
    ~IncrementStatementNode();

    void Interpret();
};

class DecrementStatementNode : public StatementNode {
private:
    IdentifierNode* IDNode;
public:
    DecrementStatementNode(IdentifierNode* in);
    ~DecrementStatementNode();

    void Interpret();
};

#endif // DECLARATION_ASSIGNMENT_H
