#if !defined(KEYWORD_H)
#define KEYWORD_H

#include <vector>
#include "../symbol.h"
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
    void Code(InstructionsClass& machineCode);
};

class WhileStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    StatementNode* sn;
public:
    WhileStatementNode(ExpressionNode* en, StatementNode* sn);
    ~WhileStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class DoWhileStatementNode : public StatementNode {
private:
    ExpressionNode* expNode;
    StatementNode* sn;
public:
    DoWhileStatementNode(ExpressionNode* en, StatementNode* sn);
    ~DoWhileStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ForStatementNode : public StatementNode {
protected:
    StatementNode* initializer;
    ExpressionNode* comparison;
    StatementNode* incrementer;
    BlockNode* blockNode;
    SymbolTable* table;
public:
    ForStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn,
        SymbolTable* table);
    ~ForStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class ForeStatementNode : public ForStatementNode {
private:
public:
    ForeStatementNode(
        StatementNode* initializer,
        ExpressionNode* comparison,
        StatementNode* incrementer,
        BlockNode* bn,
        SymbolTable* table);

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class CoutStatementNode : public StatementNode {
private:
    std::vector<ExpressionNode*> expNodes;
public:
    CoutStatementNode(std::vector<ExpressionNode*> ens);
    ~CoutStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

class CinStatementNode : public StatementNode {
private:
    std::vector<IdentifierNode*> variables;
public:
    CinStatementNode(std::vector<IdentifierNode*> vars);
    ~CinStatementNode();

    void Interpret();
    void Code(InstructionsClass& machineCode);
};

#endif // KEYWORD_H
