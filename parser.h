#if !defined(PARSER_H)
#define PARSER_H

#include "scanner.h"
#include "symbol.h"
#include "token.h"

class Parser {
private:
    Scanner* scanner;
    SymbolTable* table;

    Token Match(TokenType expected);

    void Program();
    void Block();
    void StatementGroup();
    bool Statement();
    // Statements
    void DeclarationStatement();
    void AssignmentStatement();
    void CoutStatement();

    void Expression();
    void Relational();
    void PlusMinus();
    void TimesDivide();
    void Factor();

    void Identifier();
    void Integer();
public:
    Parser(Scanner* scanner, SymbolTable* table);
    ~Parser();

    void Start();
};


#endif // PARSER_H
