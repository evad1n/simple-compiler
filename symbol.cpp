#include <algorithm>
#include <iostream>
#include "symbol.h"

SymbolTable::SymbolTable() {}

SymbolTable::~SymbolTable() {}

bool SymbolTable::Exists(const std::string& s) {
    for (auto v : this->variables) {
        if (v.label == s) {
            return true;
        }
    }
    return false;
}

void SymbolTable::AddEntry(const std::string& s) {
    if (!this->Exists(s)) {
        this->variables.push_back(Variable{ s,0 });
    }
}

int SymbolTable::GetValue(const std::string& s) {
    int idx = this->GetIndex(s);
    if (idx != -1) {
        return this->variables[idx].value;
    } else {
        std::cout << "Variable does not exist: " << s << std::endl;
        exit(EXIT_FAILURE);
    }
}

void SymbolTable::SetValue(const std::string& s, int v) {
    int idx = this->GetIndex(s);
    if (idx != -1) {
        this->variables[idx].value = v;
    } else {
        std::cout << "Variable does not exist: " << s << std::endl;
    }
}

int SymbolTable::GetIndex(const std::string& s) {
    for (int i = 0; i < this->variables.size(); i++) {
        if (this->variables[i].label == s) {
            return i;
        }
    }
    return -1;
}

int SymbolTable::GetCount() {
    return this->variables.size();
}
