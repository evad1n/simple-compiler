#if !defined(SCANNER_H)
#define SCANNER_H

#include <fstream>
#include <string>
#include "token.h"


class Scanner {
private:
    std::ifstream inFile;
    std::string fileName;
    int line;
public:
    Scanner(std::string fileName);
    ~Scanner();

    Token GetNextToken();
    std::string GetFileName() const;
    int GetLineNumber() const;

    int col;
};

// Outputs file name, line number, and column number
std::ostream& operator <<(std::ostream& out, const Scanner& s);

#endif // SCANNER_H
