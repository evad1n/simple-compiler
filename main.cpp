#include <iostream>
#include "log.h"
#include "token.h"
#include "scanner.h"
#include "node.h"

void testTokens() {
    TokenType tt = IDENTIFIER_TOKEN;
    std::string lexeme = "void";
    Token tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    tok1.CheckReserved();
    std::cout << tok1 << std::endl;
}

void testNodes() {
    StartNode* start = new StartNode(new ProgramNode(new BlockNode(new StatementGroupNode())));
    std::cout << "deleting start" << std::endl;
    delete start;

    PlusNode* plus = new PlusNode(new IntegerNode(40), new IntegerNode(50));
    std::cout << plus->Evaluate() << std::endl;
    std::cout << "deleting plusNode" << std::endl;
    delete plus;

    LessEqualNode* lte = new LessEqualNode(new IntegerNode(40), new IntegerNode(50));
    std::cout << lte->Evaluate() << std::endl;
    std::cout << "deleting lessEqualNode" << std::endl;
    delete lte;
}

void scanFile(std::string fileName) {
    Scanner scanner(fileName);
    Token t;
    do {
        t = scanner.GetNextToken();
        std::cout << t << std::endl;
    } while (t.GetTokenType() != ENDFILE_TOKEN);
}

int dog() {
    return 5;
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
    // testNodes();
    // testTokens();
}