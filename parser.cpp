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

StartNode* Parser::Start() {
    ProgramNode* pn = this->Program();
    this->Match(ENDFILE_TOKEN);
    return new StartNode(pn);
}

ProgramNode* Parser::Program() {
    this->Match(VOID_TOKEN);
    this->Match(MAIN_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();
    return new ProgramNode(bn);
}

BlockNode* Parser::Block() {
    this->Match(LEFT_BRACE_TOKEN);
    StatementGroupNode* sgn = this->StatementGroup();
    this->Match(RIGHT_BRACE_TOKEN);
    return new BlockNode(sgn);
}

StatementGroupNode* Parser::StatementGroup() {
    StatementGroupNode* sgn = new StatementGroupNode();
    StatementNode* sn;
    do {
        sn = this->Statement();
        if (sn != NULL) {
            sgn->AddStatement(sn);
        }
    } while (sn != NULL);
    return sgn;
}

// Statements

StatementNode* Parser::Statement() {
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case INT_TOKEN:
        return this->DeclarationStatement();
    case IDENTIFIER_TOKEN:
        return this->AssignmentStatement();
    case COUT_TOKEN:
        return this->CoutStatement();
    }
    return NULL;
}


DeclarationStatementNode* Parser::DeclarationStatement() {
    this->Match(INT_TOKEN);
    IdentifierNode* in = this->Identifier();
    this->Match(SEMICOLON_TOKEN);
    return new DeclarationStatementNode(in);
}

AssignmentStatementNode* Parser::AssignmentStatement() {
    IdentifierNode* in = this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    return new AssignmentStatementNode(en, in);
}

CoutStatementNode* Parser::CoutStatement() {
    this->Match(COUT_TOKEN);
    this->Match(INSERTION_TOKEN);
    ExpressionNode* en = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    return new CoutStatementNode(en);
}

// Expressions

ExpressionNode* Parser::Expression() {
    return this->Relational();
}

ExpressionNode* Parser::Relational() {
    ExpressionNode* en = this->PlusMinus();

    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case LESS_TOKEN:
        this->Match(t);
        en = new LessNode(en, this->PlusMinus());
        break;
    case LESS_EQUAL_TOKEN:
        this->Match(t);
        en = new LessEqualNode(en, this->PlusMinus());
        break;
    case GREATER_TOKEN:
        this->Match(t);
        en = new GreaterNode(en, this->PlusMinus());
        break;
    case GREATER_EQUAL_TOKEN:
        this->Match(t);
        en = new GreaterEqualNode(en, this->PlusMinus());
        break;
    case EQUAL_TOKEN:
        this->Match(t);
        en = new EqualNode(en, this->PlusMinus());
        break;
    case NOT_EQUAL_TOKEN:
        this->Match(t);
        en = new NotEqualNode(en, this->PlusMinus());
        break;
    }
    return en;
}

ExpressionNode* Parser::PlusMinus() {
    ExpressionNode* en = this->TimesDivide();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case PLUS_TOKEN:
            this->Match(t);
            en = new PlusNode(en, this->TimesDivide());
            break;
        case MINUS_TOKEN:
            this->Match(t);
            en = new MinusNode(en, this->TimesDivide());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::TimesDivide() {
    ExpressionNode* en = this->Factor();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case MULTIPLY_TOKEN:
            this->Match(t);
            en = new TimesNode(en, this->Factor());
            break;
        case DIVIDE_TOKEN:
            this->Match(t);
            en = new DivideNode(en, this->Factor());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Factor() {
    ExpressionNode* en;
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case IDENTIFIER_TOKEN:
        en = this->Identifier();
        break;
    case INTEGER_TOKEN:
        en = this->Integer();
        break;
    case LEFT_PAREN_TOKEN:
        this->Match(LEFT_PAREN_TOKEN);
        en = this->Expression();
        this->Match(RIGHT_PAREN_TOKEN);
        break;
    default:
        std::cerr << "Error: expected factor type, got " << Token::GetTokenTypeName(t) << std::endl;
    }
    return en;
}

IdentifierNode* Parser::Identifier() {
    Token t = this->Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(t.GetLexeme(), this->table);
}

IntegerNode* Parser::Integer() {
    Token t = this->Match(INTEGER_TOKEN);
    int i = atoi(t.GetLexeme().c_str());
    return new IntegerNode(i);
}
