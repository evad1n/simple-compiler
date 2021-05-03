#include <iostream>
#include <string.h>
#include "log.h"
#include "token.h"
#include "scanner.h"
#include "nodes/node.h"
#include "symbol.h"
#include "parser.h"

void testTokens() {
    TokenType tt = IDENTIFIER_TOKEN;
    std::string lexeme = "void";
    Token tok1(tt, lexeme);
    std::cout << tok1 << std::endl;
    tok1.CheckReserved();
    std::cout << tok1 << std::endl;
}

void printTokens(std::string fileName) {
    Scanner scanner(fileName);
    Token t;
    do {
        t = scanner.GetNextToken();
        std::cout << t << std::endl;
    } while (t.GetTokenType() != ENDFILE_TOKEN);
}

void machine() {
    unsigned char mCode[] = { 0x55, 0x8B, 0xEC, 0X5d, 0XC3 };
    std::cout << "About to Execute the machine code...\n";
    void* ptr = mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr;
    f(); // call the array as if it were a function
    std::cout << "There and back again!\n\n";
}

void interpret(std::string fileName) {
    Scanner scanner(fileName);
    Parser parser(&scanner);
    StartNode* start = parser.Start();
    start->Interpret();
    delete start;
}

void codeAndExecute(std::string fileName) {
    // Create scanner, symbol table, and parser objects.
    Scanner scanner(fileName);
    Parser parser(&scanner);

    // Do the parsing, which results in a parse tree.
    StartNode* start = parser.Start();

    // Create the machine code instructions from the parse tree
    InstructionsClass machineCode;
    start->Code(machineCode);
    machineCode.Finish();
    // machineCode.PrintAllMachineCodes();

    // Execute the machine code instructions previously created
    machineCode.Execute();

    // cleanup recursively
    delete start;
}

int main(int argc, char const* argv[]) {
    LOG("LOGGING");
    bool interpretOnly = false;
    bool print = false;

    if (argc < 2) {
        std::cout << "No input files provided" << std::endl;
    } else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-i") == 0) {
                interpretOnly = true;
            } else if (strcmp(argv[i], "-p") == 0) {
                print = true;
            } else {
                if (print) {
                    printTokens(argv[i]);
                }
                if (interpretOnly) {
                    interpret(argv[i]);
                } else {
                    codeAndExecute(argv[i]);
                }
            }
        }
    }
    // testTokens();
    // machine();

    return 0;
}