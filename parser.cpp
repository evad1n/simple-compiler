#include <iostream>
#include "parser.h"


Parser::Parser(Scanner* scanner)
    : scanner(scanner) {
    SymbolTable* global = new SymbolTable();
    this->scopes = std::vector<SymbolTable*>{ global };
    this->scopeStack = std::vector<SymbolTable*>{ global };
    this->currentScope = 0;
}

Parser::~Parser() {
    delete this->scanner;
}

Token Parser::Match(TokenType expected) {
    Token t = this->scanner->GetNextToken();
    if (t.GetTokenType() != expected) {
        std::cerr << "Error in parser match. " << std::endl;
        std::cerr << "Expected token type " <<
            Token::GetTokenTypeName(expected) <<
            ", but got type " << t.GetTokenTypeName() << ": " << t << std::endl;
        exit(1);
    }
    return t;
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
    this->currentScope++;
    SymbolTable* scope = new SymbolTable();
    this->scopes.push_back(scope);
    this->scopeStack.push_back(scope);
    StatementGroupNode* sgn = this->StatementGroup();
    this->scopeStack.pop_back();
    this->currentScope--;
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
    case INT_TYPE_TOKEN:
        return this->DeclarationStatement();
    case IDENTIFIER_TOKEN:
        return this->AssignmentStatement();
    case IF_TOKEN:
        return this->IfElseStatement();
    case WHILE_TOKEN:
        return this->WhileStatement();
    case FOR_TOKEN:
        return this->ForStatement();
    case FORE_TOKEN:
        return this->ForeStatement();
    case COUT_TOKEN:
        return this->CoutStatement();
    case CIN_TOKEN:
        return this->CinStatement();
    case LEFT_BRACE_TOKEN:
        return this->Block();
    }
    return NULL;
}



DeclarationStatementNode* Parser::DeclarationStatement() {
    this->Match(INT_TYPE_TOKEN);
    IdentifierNode* in = this->Identifier();
    // Optional assignment at same time
    Token t = this->scanner->PeekNextToken();
    TokenType tt = t.GetTokenType();
    switch (tt) {
    case SEMICOLON_TOKEN:
        this->Match(tt);
        return new DeclarationStatementNode(in);
    case ASSIGNMENT_TOKEN:
    {
        this->Match(tt);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new DeclarationAssignmentStatementNode(in, en);
    }
    default:
        std::cerr << "Error: invalid declaration: " << t << std::endl;
        break;
    }
    return NULL;
}

StatementNode* Parser::AssignmentStatement() {
    IdentifierNode* in = this->Identifier();
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case ASSIGNMENT_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new AssignmentStatementNode(in, en);
    }
    case PLUS_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new PlusEqualsStatementNode(in, en);
    }
    case MINUS_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new MinusEqualsStatementNode(in, en);
    }
    case MULTIPLY_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new MultiplyEqualsStatementNode(in, en);
    }
    case DIVIDE_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        this->Match(SEMICOLON_TOKEN);
        return new DivideEqualsStatementNode(in, en);
    }
    case INCREMENT_TOKEN:
    {
        this->Match(t);
        this->Match(SEMICOLON_TOKEN);
        return new IncrementStatementNode(in);
    }
    case DECREMENT_TOKEN:
    {
        this->Match(t);
        this->Match(SEMICOLON_TOKEN);
        return new DecrementStatementNode(in);
    }
    default:
        std::cerr << "Error: invalid assignment: " << t << std::endl;
        break;
    }
    return NULL;
}

IfElseStatementNode* Parser::IfElseStatement() {
    this->Match(IF_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    ExpressionNode* ifExp = this->Expression();
    this->Match(RIGHT_PAREN_TOKEN);
    StatementNode* ifBlock;
    if (this->scanner->PeekNextToken().GetTokenType() == LEFT_BRACE_TOKEN) {
        ifBlock = this->Block();
    } else {
        ifBlock = this->Statement();
    }

    StatementNode* elseBlock = NULL;
    if (this->scanner->PeekNextToken().GetTokenType() == ELSE_TOKEN) {
        this->Match(ELSE_TOKEN);
        if (this->scanner->PeekNextToken().GetTokenType() == IF_TOKEN) {
            return new IfElseStatementNode(ifExp, ifBlock, this->IfElseStatement());
        }
        if (this->scanner->PeekNextToken().GetTokenType() == LEFT_BRACE_TOKEN) {
            elseBlock = this->Block();
        } else {
            elseBlock = this->Statement();
        }
    }
    return new IfElseStatementNode(ifExp, ifBlock, elseBlock);
}

WhileStatementNode* Parser::WhileStatement() {
    this->Match(WHILE_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    ExpressionNode* en = this->Expression();
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();
    return new WhileStatementNode(en, bn);
}

ForStatementNode* Parser::ForStatement() {
    this->Match(FOR_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    StatementNode* initializer = this->Statement();
    ExpressionNode* comparison = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    IdentifierNode* in = this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = this->Expression();
    AssignmentStatementNode* incrementer = new AssignmentStatementNode(in, en);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();
    return new ForStatementNode(initializer, comparison, incrementer, bn);
}

ForeStatementNode* Parser::ForeStatement() {
    this->Match(FORE_TOKEN);
    this->Match(LEFT_PAREN_TOKEN);
    StatementNode* initializer = this->Statement();
    ExpressionNode* comparison = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    IdentifierNode* in = this->Identifier();
    this->Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = this->Expression();
    AssignmentStatementNode* incrementer = new AssignmentStatementNode(in, en);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();
    return new ForeStatementNode(initializer, comparison, incrementer, bn);
}

CoutStatementNode* Parser::CoutStatement() {
    this->Match(COUT_TOKEN);
    std::vector<ExpressionNode*> ens;
    do {
        this->Match(INSERTION_TOKEN);
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case ENDL_TOKEN:
            this->Match(t);
            ens.push_back(NULL);
            break;
        default:
            ens.push_back(this->Expression());
            break;
        }
    } while (this->scanner->PeekNextToken().GetTokenType() == INSERTION_TOKEN);
    this->Match(SEMICOLON_TOKEN);
    return new CoutStatementNode(ens);
}

CinStatementNode* Parser::CinStatement() {
    this->Match(CIN_TOKEN);
    std::vector<IdentifierNode*> ids;
    do {
        this->Match(EXTRACTION_TOKEN);
        ids.push_back(this->Identifier());
    } while (this->scanner->PeekNextToken().GetTokenType() == EXTRACTION_TOKEN);
    this->Match(SEMICOLON_TOKEN);
    return new CinStatementNode(ids);
}

// Expressions

ExpressionNode* Parser::Expression() {
    // Return lowest precedence operator first
    return this->Or();
}

ExpressionNode* Parser::Exponent() {
    ExpressionNode* en = this->Factor();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case EXPONENT_TOKEN:
            this->Match(t);
            en = new ExponentNode(en, this->Factor());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::TimesDivide() {
    ExpressionNode* en = this->Exponent();

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



ExpressionNode* Parser::BitwiseAnd() {
    ExpressionNode* en = this->Relational();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case BITWISE_AND_TOKEN:
            this->Match(t);
            en = new BitwiseOrNode(en, this->PlusMinus());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::BitwiseOr() {
    ExpressionNode* en = this->BitwiseAnd();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case BITWISE_OR_TOKEN:
            this->Match(t);
            en = new BitwiseOrNode(en, this->PlusMinus());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::And() {
    ExpressionNode* en = this->BitwiseOr();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case AND_TOKEN:
            this->Match(t);
            en = new AndNode(en, this->Expression());
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Or() {
    ExpressionNode* en = this->And();

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case OR_TOKEN:
            this->Match(t);
            en = new OrNode(en, this->Expression());
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
        exit(EXIT_FAILURE);
    }
    return en;
}

IdentifierNode* Parser::Identifier() {
    Token t = this->Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(t.GetLexeme(), this->scopeStack[this->currentScope]);
}

IntegerNode* Parser::Integer() {
    Token t = this->Match(INTEGER_TOKEN);
    int i = atoi(t.GetLexeme().c_str());
    return new IntegerNode(i);
}
