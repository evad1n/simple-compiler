#include <iostream>
#include "log.h"
#include "token.h"
#include "scanner.h"

void testTokens() {
    TokenType tt = IDENTIFIER_TOKEN;
    std::string lexeme = "void";
    Token tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    tok1.CheckReserved();
    std::cout << tok1 << std::endl;
}

void scanFile(std::string fileName) {
    Scanner scanner(fileName);
    Token t;
    do {
        t = scanner.GetNextToken();
        std::cout << t << std::endl;
    } while (t.GetTokenType() != ENDFILE_TOKEN);
}

int main(int argc, char const* argv[]) {
    LOG("LOGGING");
    if (argc < 2) {
        std::cout << "No input files provided" << std::endl;
    } else {
        for (int i = 1; i < argc; i++) {
            scanFile(argv[i]);
        }
    }
    // testTokens();
}