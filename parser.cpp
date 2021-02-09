#include <iostream>
#include "parser.h"

Parser::Parser(Scanner* scanner, SymbolTable* table)
    : scanner(scanner), table(table) {}

Parser::~Parser() {}

Token Parser::Match(TokenType expected) {
    Token curr = this->scanner->GetNextToken();
    if (curr.GetTokenType() != expected) {
        std::cerr << "Error in parser match. " << std::endl;
        std::cerr << "Expected token type " <<
            Token::GetTokenTypeName(expected) <<
            ", but got type " << curr.GetTokenTypeName() << std::endl;
        exit(1);
    }

    return curr;
}

void Parser::Start() {
    this->Program();
    this->Match(ENDFILE_TOKEN);
}

void Parser::Program() {
    this->Match(VOID_TOKEN);
    this->Match(MAIN_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    this->Match(RIGHT_PAREN_TOKEN);
    this->Block();
}

void Parser::Block() {
    this->Match(LEFT_BRACE_TOKEN);
    this->StatementGroup();
    this->Match(RIGHT_BRACE_TOKEN);
}

void Parser::StatementGroup() {
    bool valid;
    do {
        valid = this->Statement();
    } while (valid);
}

// Statements

bool Parser::Statement() {
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case INT_TOKEN:
        this->DeclarationStatement();
        break;
    case IDENTIFIER_TOKEN:
        this->AssignmentStatement();
        return true;
    case COUT_TOKEN:
        this->CoutStatement();
        return true;
    default:
        return false;
    }
}


void Parser::DeclarationStatement() {
    this->Match(INT_TOKEN);
    this->Identifier();
    this->Match(SEMICOLON_TOKEN);
}

void Parser::AssignmentStatement() {
    this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    this->Expression();
    this->Match(SEMICOLON_TOKEN);
}

void Parser::CoutStatement() {
    this->Match(COUT_TOKEN);
    this->Match(INSERTION_TOKEN);
    this->Expression();
    this->Match(SEMICOLON_TOKEN);
}

// Expressions

void Parser::Expression() {
    this->Relational();
}

void Parser::Relational() {
    this->PlusMinus();

    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case LESS_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    case LESS_EQUAL_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    case GREATER_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    case GREATER_EQUAL_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    case EQUAL_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    case NOT_EQUAL_TOKEN:
        this->Match(t);
        this->PlusMinus();
        break;
    default:
        break;
    }

}

void Parser::PlusMinus() {
    this->TimesDivide();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case PLUS_TOKEN:
            this->Match(t);
            this->TimesDivide();
            break;
        case MINUS_TOKEN:
            this->Match(t);
            this->TimesDivide();
            break;
        default:
            return;
        }
    }
}

void Parser::TimesDivide() {
    this->Factor();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case MULTIPLY_TOKEN:
            this->Match(t);
            this->Factor();
            break;
        case DIVIDE_TOKEN:
            this->Match(t);
            this->Factor();
            break;
        default:
            return;
        }
    }
}

void Parser::Factor() {
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case IDENTIFIER_TOKEN:
        this->Identifier();
        break;
    case INTEGER_TOKEN:
        this->Integer();
        break;
    case LEFT_PAREN_TOKEN:
        this->Match(LEFT_PAREN_TOKEN);
        this->Expression();
        this->Match(RIGHT_PAREN_TOKEN);
        break;
    default:
        std::cerr << "Error: expected factor type, got " << Token::GetTokenTypeName(t) << std::endl;
    }
}

void Parser::Identifier() {
    this->Match(IDENTIFIER_TOKEN);
}

void Parser::Integer() {
    this->Match(INTEGER_TOKEN);
}
