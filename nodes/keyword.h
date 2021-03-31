#if !defined(KEYWORD_H)
#define KEYWORD_H

#include <vector>
#include "base.h"
#include "value.h"

class IfElseStatementNode;
class WhileStatementNode;
class ForStatementNode;
class ForeStatementNode;
class CoutStatementNode;
class CinStatementNode;

class IfElseStatementNode : public StatementNode {
private:
    ExpressionNode* ifExp;
    StatementNode* ifBranch;
    StatementNode* elseBranch;
public:
    IfElseStatementNode(ExpressionNode* ifExp, StatementNode* ifBranch, StatementNode* elseBranch);
    ~IfElseStatementNode();

    void Interpret();
};

class WhileStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    BlockNode* blockNode;
public:
    WhileStatementNode(ExpressionNode* en, BlockNode* bn);
    ~WhileStatementNode();

    void Interpret();
};

class ForStatementNode : public StatementNode {
private:
    StatementNode* initializer;
    ExpressionNode* comparison;
    StatementNode* incrementer;
    BlockNode* blockNode;
public:
    ForStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn);
    ~ForStatementNode();

    void Interpret();
};

class ForeStatementNode : public StatementNode {
private:
    StatementNode* initializer;
    ExpressionNode* comparison;
    StatementNode* incrementer;
    BlockNode* blockNode;
public:
    ForeStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn);
    ~ForeStatementNode();

    void Interpret();
};

class CoutStatementNode : public StatementNode {
private:
    std::vector<ExpressionNode*> expNodes;
public:
    CoutStatementNode(std::vector<ExpressionNode*> ens);
    ~CoutStatementNode();

    void Interpret();
};

class CinStatementNode : public StatementNode {
private:
    std::vector<IdentifierNode*> variables;
public:
    CinStatementNode(std::vector<IdentifierNode*> vars);
    ~CinStatementNode();

    void Interpret();
};

#endif // KEYWORD_H
