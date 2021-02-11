#if !defined(PARSER_H)
#define PARSER_H

#include "scanner.h"
#include "symbol.h"
#include "token.h"
#include "node.h"

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
    AssignmentStatementNode* AssignmentStatement();
    CoutStatementNode* CoutStatement();

    ExpressionNode* Expression();
    ExpressionNode* Relational();
    ExpressionNode* PlusMinus();
    ExpressionNode* TimesDivide();
    ExpressionNode* Factor();

    IdentifierNode* Identifier();
    IntegerNode* Integer();
public:
    Parser(Scanner* scanner, SymbolTable* table);
    ~Parser();

    StartNode* Start();
};


#endif // PARSER_H
