#if !defined(TOKEN_H)
#define TOKEN_H

#include <string>
#include <iostream>

enum TokenType {
    // Reserved words
    VOID_TOKEN, MAIN_TOKEN, TRUE_TOKEN, FALSE_TOKEN, AND_TOKEN, OR_TOKEN, DO_TOKEN, INT_TYPE_TOKEN, COUT_TOKEN, CIN_TOKEN, ENDL_TOKEN, IF_TOKEN, ELSE_TOKEN, WHILE_TOKEN, FOR_TOKEN, FORE_TOKEN,
    RESERVED_COUNT,
    // Scope tokens
    SEMICOLON_TOKEN,
    LEFT_PAREN_TOKEN, RIGHT_PAREN_TOKEN,
    LEFT_BRACE_TOKEN, RIGHT_BRACE_TOKEN,
    // Relational tokens
    LESS_TOKEN, LESS_EQUAL_TOKEN,
    GREATER_TOKEN, GREATER_EQUAL_TOKEN,
    EQUAL_TOKEN, NOT_EQUAL_TOKEN,
    BITWISE_AND_TOKEN, BITWISE_OR_TOKEN,
    NEGATIVE_TOKEN,
    TERNARY_QUESTION_TOKEN, TERNARY_COLON_TOKEN,
    NOT_TOKEN,
    PLUS_TOKEN, MINUS_TOKEN, MULTIPLY_TOKEN, DIVIDE_TOKEN, EXPONENT_TOKEN,
    INSERTION_TOKEN, EXTRACTION_TOKEN, ASSIGNMENT_TOKEN,
    PLUS_EQUALS_TOKEN, MINUS_EQUALS_TOKEN, MULTIPLY_EQUALS_TOKEN, DIVIDE_EQUALS_TOKEN,
    INCREMENT_TOKEN, DECREMENT_TOKEN,
    // Other token types
    IDENTIFIER_TOKEN, INTEGER_TOKEN,
    BAD_TOKEN, ENDFILE_TOKEN
};

class Token {
private:
    TokenType type;
    std::string lexeme;
    std::string fileName;
    int line, col;
public:
    static const std::string& GetTokenTypeName(TokenType type);

    Token();
    Token(TokenType type, const std::string& lexeme);
    Token(TokenType type, const std::string& lexeme, std::string fileName, int line, int col);
    ~Token();

    const std::string& GetTokenTypeName() const;
    TokenType GetTokenType() const;
    std::string GetLexeme() const;

    std::string ToString() const;

    // If this lexeme is one of the reserved words, then assign it that token
    void CheckReserved();

    // Outputs token type, name, and lexeme, along with file location info
    friend std::ostream& operator <<(std::ostream& out, const Token& tc);
};


#endif // TOKEN_H
