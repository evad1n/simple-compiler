#if !defined(PARSER_H)
#define PARSER_H

#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "nodes/node.h"

class Parser {
private:
    Scanner* scanner;
    SymbolTable table;

    Token Match(TokenType expected);

    ProgramNode* Program();
    BlockNode* Block();
    StatementGroupNode* StatementGroup();
    StatementNode* Statement();
    // Statements
    DeclarationStatementNode* DeclarationStatement();
    DeclarationAssignmentStatementNode* DeclarationAssignmentStatement();
    StatementNode* AssignmentStatement(bool semicolon = true);
    IfElseStatementNode* IfElseStatement();
    WhileStatementNode* WhileStatement();
    DoWhileStatementNode* DoWhileStatement();
    ForStatementNode* ForStatement();
    ForeStatementNode* ForeStatement();
    CoutStatementNode* CoutStatement();
    CinStatementNode* CinStatement();

    ExpressionNode* Expression(bool parens = false);
    ExpressionNode* Ternary(bool parens = false);
    ExpressionNode* Or(bool parens = false);
    ExpressionNode* And(bool parens = false);
    ExpressionNode* BitwiseOr(bool parens = false);
    ExpressionNode* BitwiseAnd(bool parens = false);
    ExpressionNode* Relational(bool parens = false);
    ExpressionNode* BitShift(bool parens = false);
    ExpressionNode* PlusMinus(bool parens = false);
    ExpressionNode* TimesDivide(bool parens = false);
    ExpressionNode* Exponent(bool parens = false);
    ExpressionNode* Factor(bool parens = false);

    IdentifierNode* Identifier();
    IntegerNode* Integer();
public:
    Parser(Scanner* scanner);
    ~Parser();

    StartNode* Start();
};


#endif // PARSER_H
