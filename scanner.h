#if !defined(SCANNER_H)
#define SCANNER_H

#include <fstream>
#include <string>
#include "token.h"


class Scanner {
private:
    std::ifstream inFile;
    std::string fileName;
    int line, col;
public:
    Scanner(std::string fileName);
    ~Scanner();

    Token GetNextToken();
    Token PeekNextToken();

    std::string GetFileName() const;
    int GetLineNumber() const;

    // Outputs file name, line number, and column number
    friend std::ostream& operator <<(std::ostream& out, const Scanner& s);
};


#endif // SCANNER_H
