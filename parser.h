#if !defined(PARSER_H)
#define PARSER_H

#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "nodes/node.h"

class Parser {
private:
    Scanner* scanner;
    std::vector<SymbolTable*> scopes;
    std::vector<SymbolTable*> scopeStack;
    int currentScope;

    Token Match(TokenType expected);

    ProgramNode* Program();
    BlockNode* Block(bool newScope = true);
    StatementGroupNode* StatementGroup();
    StatementNode* Statement();
    // Statements
    DeclarationStatementNode* DeclarationStatement();
    DeclarationAssignmentStatementNode* DeclarationAssignmentStatement();
    StatementNode* AssignmentStatement(bool semicolon = true);
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
    ExpressionNode* BitwiseAnd();
    ExpressionNode* BitwiseOr();
    ExpressionNode* And();
    ExpressionNode* Or();
    ExpressionNode* Ternary();
    ExpressionNode* Factor();

    IdentifierNode* Identifier();
    IntegerNode* Integer();
public:
    Parser(Scanner* scanner);
    ~Parser();

    StartNode Start();
};


#endif // PARSER_H
