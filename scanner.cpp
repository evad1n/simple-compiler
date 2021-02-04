#include <fstream>
#include <sstream>
#include <string>
#include <iomanip> 

#include "log.h"
#include "scanner.h"
#include "token.h"
#include "state_machine.h"


Scanner::Scanner(std::string fileName)
    : fileName(fileName), line(1), col(1) {
    this->inFile.open(fileName, std::ios::binary);
    if (!this->inFile.is_open()) {
        std::cerr << "Failed to open file '" << fileName << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
}

Scanner::~Scanner() {
    this->inFile.close();
}

Token Scanner::GetNextToken() {
    StateMachine sm = StateMachine();
    MachineState state;
    char next;
    TokenType type;
    std::string lexeme = "";
    do {
        // Get next char
        next = this->inFile.get();
        // LOG("next char: " + next);
        state = sm.UpdateState(next, type);
        lexeme += next;
        this->col++;
        // Check for tabs
        if (next == '\t') {
            this->col += 3;
        }
        // No changes while in start state
        if (state == START_STATE) {
            lexeme = "";
        }
        // Increment lines
        if (next == '\n' && state != CANTMOVE_STATE) {
            this->line++;
            this->col = 1;
        }
    } while (state != CANTMOVE_STATE);

    // Put back last read character in (will be start of next token)
    this->inFile.unget();
    this->col--;
    lexeme.pop_back();

    if (type == BAD_TOKEN) {
        std::cout << *this << "\e[31mERROR:\e[0m Bad token parsed: \e[31m" << next << "\e[0m in lexeme '\e[31m" << lexeme << "\e[0m'" << std::endl;
        exit(EXIT_FAILURE);
    }


    Token tok = Token(type, lexeme, this->GetFileName(), this->line, this->col - lexeme.length());
    LOG("type #: " + tok.GetTokenType());
    LOG("before check reserved: " + tok.GetTokenTypeName());
    tok.CheckReserved();
    LOG("after check reserved: " + tok.GetTokenTypeName());
    return tok;
}

std::string Scanner::GetFileName() const {
    return this->fileName;
}

int Scanner::GetLineNumber() const {
    return this->line;
}

std::ostream& operator <<(std::ostream& out, const Scanner& s) {
    std::stringstream ss;
    ss << s.GetFileName() << ":" << s.GetLineNumber() << ":" << s.col << ": ";
    out.setf(std::ios::left);
    out << "\e[1m" << std::setw(s.GetFileName().length() + 8) << ss.str() << "\e[0m";
    return out;
}
