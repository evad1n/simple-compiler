#if !defined(PARSER_H)
#define PARSER_H

#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "nodes/node.h"

class Parser {
private:
    Scanner* scanner;
    SymbolTable* table;

    Token Match(TokenType expected);

    ProgramNode* Program();
    BlockNode* Block();
    StatementGroupNode* StatementGroup();
    StatementNode* Statement();
    // Statements
    DeclarationStatementNode* DeclarationStatement();
    DeclarationAssignmentStatementNode* DeclarationAssignmentStatement();
    StatementNode* AssignmentStatement();
    IfElseStatementNode* IfElseStatement();
    WhileStatementNode* WhileStatement();
    ForStatementNode* ForStatement();
    ForeStatementNode* ForeStatement();
    CoutStatementNode* CoutStatement();
    CinStatementNode* CinStatement();

    ExpressionNode* Expression();
    ExpressionNode* Exponent();
    ExpressionNode* TimesDivide();
    ExpressionNode* PlusMinus();
    ExpressionNode* Relational();
    ExpressionNode* And();
    ExpressionNode* Or();
    ExpressionNode* Factor();

    IdentifierNode* Identifier();
    IntegerNode* Integer();
public:
    Parser(Scanner* scanner, SymbolTable* table);
    ~Parser();

    StartNode* Start();
};


#endif // PARSER_H
