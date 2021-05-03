#include <iostream>
#include <vector>
#include "symbol.h"

SymbolTable::SymbolTable() {}

SymbolTable::~SymbolTable() {}

bool SymbolTable::Exists(const std::string& s) {
    for (int i = this->variables.size() - 1; i >= this->NearestScope(); i--) {
        if (this->variables[i].label == s) {
            return true;
        }
    }
    return false;
}

void SymbolTable::AddEntry(const std::string& s) {
    if (!this->Exists(s)) {
        this->variables.push_back(Variable{ s,0 });
    } else {
        std::cout << "Redeclaration of variable: " << s << std::endl;
        exit(EXIT_FAILURE);
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
    // Reverse iterate so nearest scope is taken
    for (int i = this->variables.size() - 1; i >= 0; i--) {
        if (this->variables[i].label == s) {
            return i;
        }
    }
    return -1;
}

int SymbolTable::GetCount() {
    return this->variables.size();
}

void SymbolTable::NewScope() {
    this->scopeMarkers.push_back(this->GetCount());
}

void SymbolTable::LeaveScope() {
    for (int i = this->variables.size() - 1; i >= this->NearestScope(); i--) {
        this->variables.pop_back();
    }
    this->scopeMarkers.pop_back();
}

int SymbolTable::NearestScope() {
    return this->scopeMarkers[this->scopeMarkers.size() - 1];
}