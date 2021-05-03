#include <iostream>
#include "parser.h"


Parser::Parser(Scanner* scanner)
    : scanner(scanner) {
    this->table = SymbolTable();
}

Parser::~Parser() {}

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
    StatementGroupNode* sgn = this->StatementGroup();
    this->Match(RIGHT_BRACE_TOKEN);
    return new BlockNode(sgn, &this->table);
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

StatementNode* Parser::AssignmentStatement(bool semicolon) {
    IdentifierNode* in = this->Identifier();
    TokenType t = this->scanner->PeekNextToken().GetTokenType();

    StatementNode* sn = NULL;
    switch (t) {
    case ASSIGNMENT_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        sn = new AssignmentStatementNode(in, en);
        break;
    }
    case PLUS_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        sn = new PlusEqualsStatementNode(in, en);
        break;
    }
    case MINUS_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        sn = new MinusEqualsStatementNode(in, en);
        break;
    }
    case MULTIPLY_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        sn = new MultiplyEqualsStatementNode(in, en);
        break;
    }
    case DIVIDE_EQUALS_TOKEN:
    {
        this->Match(t);
        ExpressionNode* en = this->Expression();
        sn = new DivideEqualsStatementNode(in, en);
        break;
    }
    case INCREMENT_TOKEN:
    {
        this->Match(t);
        sn = new IncrementStatementNode(in);
        break;
    }
    case DECREMENT_TOKEN:
    {
        this->Match(t);
        sn = new DecrementStatementNode(in);
        break;
    }
    default:
        std::cerr << "Error: invalid assignment: " << t << std::endl;
        break;
    }
    if (semicolon)
        this->Match(SEMICOLON_TOKEN);
    return sn;
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
    StatementNode* incrementer = this->AssignmentStatement(false);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();

    return new ForStatementNode(initializer, comparison, incrementer, bn, &this->table);
}

ForeStatementNode* Parser::ForeStatement() {
    this->Match(FORE_TOKEN);

    this->Match(LEFT_PAREN_TOKEN);
    StatementNode* initializer = this->Statement();
    ExpressionNode* comparison = this->Expression();
    this->Match(SEMICOLON_TOKEN);
    StatementNode* incrementer = this->AssignmentStatement(false);
    this->Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = this->Block();

    return new ForeStatementNode(initializer, comparison, incrementer, bn, &this->table);
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

ExpressionNode* Parser::Expression(bool parens) {
    // Return lowest precedence operator first
    return this->Ternary(parens);
}

ExpressionNode* Parser::Ternary(bool parens) {
    ExpressionNode* en = this->Or(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case TERNARY_QUESTION_TOKEN:
        {
            this->Match(t);
            ExpressionNode* second = this->Or();
            this->Match(TERNARY_COLON_TOKEN);
            en = new TernaryOperatorNode(en, second, this->Or(parens));
            break;
        }
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Or(bool parens) {
    ExpressionNode* en = this->And(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case OR_TOKEN:
            this->Match(t);
            en = new OrNode(en, this->And(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::And(bool parens) {
    ExpressionNode* en = this->BitwiseOr(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case AND_TOKEN:
            this->Match(t);
            en = new AndNode(en, this->BitwiseOr(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::BitwiseOr(bool parens) {
    ExpressionNode* en = this->BitwiseAnd(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case BITWISE_OR_TOKEN:
            this->Match(t);
            en = new BitwiseOrNode(en, this->BitwiseAnd(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::BitwiseAnd(bool parens) {
    ExpressionNode* en = this->Relational(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case BITWISE_AND_TOKEN:
            this->Match(t);
            en = new BitwiseAndNode(en, this->Relational(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Relational(bool parens) {
    ExpressionNode* en = this->BitShift(parens);

    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case LESS_TOKEN:
        this->Match(t);
        en = new LessNode(en, this->BitShift(parens));
        break;
    case LESS_EQUAL_TOKEN:
        this->Match(t);
        en = new LessEqualNode(en, this->BitShift(parens));
        break;
    case GREATER_TOKEN:
        this->Match(t);
        en = new GreaterNode(en, this->BitShift(parens));
        break;
    case GREATER_EQUAL_TOKEN:
        this->Match(t);
        en = new GreaterEqualNode(en, this->BitShift(parens));
        break;
    case EQUAL_TOKEN:
        this->Match(t);
        en = new EqualNode(en, this->BitShift(parens));
        break;
    case NOT_EQUAL_TOKEN:
        this->Match(t);
        en = new NotEqualNode(en, this->BitShift(parens));
        break;
    }
    return en;
}

ExpressionNode* Parser::BitShift(bool parens) {
    ExpressionNode* en = this->PlusMinus(parens);

    if (parens) {
        for (;;) {
            TokenType t = this->scanner->PeekNextToken().GetTokenType();
            switch (t) {
            case INSERTION_TOKEN:
                this->Match(t);
                en = new LeftShiftNode(en, this->PlusMinus(parens));
                break;
            case EXTRACTION_TOKEN:
                this->Match(t);
                en = new RightShiftNode(en, this->PlusMinus(parens));
                break;
            default:
                return en;
            }
        }
    } else {
        return en;
    }
}

ExpressionNode* Parser::PlusMinus(bool parens) {
    ExpressionNode* en = this->TimesDivide(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case PLUS_TOKEN:
            this->Match(t);
            en = new PlusNode(en, this->TimesDivide(parens));
            break;
        case MINUS_TOKEN:
            this->Match(t);
            en = new MinusNode(en, this->TimesDivide(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::TimesDivide(bool parens) {
    ExpressionNode* en = this->Exponent(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case MULTIPLY_TOKEN:
            this->Match(t);
            en = new TimesNode(en, this->Exponent(parens));
            break;
        case DIVIDE_TOKEN:
            this->Match(t);
            en = new DivideNode(en, this->Exponent(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Exponent(bool parens) {
    ExpressionNode* en = this->Factor(parens);

    for (;;) {
        TokenType t = this->scanner->PeekNextToken().GetTokenType();
        switch (t) {
        case EXPONENT_TOKEN:
            this->Match(t);
            en = new ExponentNode(en, this->Factor(parens));
            break;
        default:
            return en;
        }
    }
}

ExpressionNode* Parser::Factor(bool parens) {
    ExpressionNode* en;
    TokenType t = this->scanner->PeekNextToken().GetTokenType();
    switch (t) {
    case NOT_TOKEN:
        this->Match(t);
        en = new NotNode(this->Expression(parens));
        break;
    case TRUE_TOKEN:
        this->Match(t);
        en = new TrueNode();
        break;
    case FALSE_TOKEN:
        this->Match(t);
        en = new FalseNode();
        break;
    case NEGATIVE_TOKEN:
        this->Match(t);
        en = new NegativeNode(this->Expression(parens));
        break;
    case IDENTIFIER_TOKEN:
        en = this->Identifier();
        break;
    case INTEGER_TOKEN:
        en = this->Integer();
        break;
    case LEFT_PAREN_TOKEN:
        this->Match(LEFT_PAREN_TOKEN);
        en = this->Expression(true);
        this->Match(RIGHT_PAREN_TOKEN);
        break;
    default:
        std::cerr << "Error: expected factor type, got " << Token::GetTokenTypeName(t) << std::endl;
        std::cerr << this->scanner->PeekNextToken() << std::endl;
        exit(EXIT_FAILURE);
    }
    return en;
}

IdentifierNode* Parser::Identifier() {
    Token t = this->Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(t.GetLexeme(), &this->table);
}

IntegerNode* Parser::Integer() {
    Token t = this->Match(INTEGER_TOKEN);
    int i = atoi(t.GetLexeme().c_str());
    return new IntegerNode(i);
}
