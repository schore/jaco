// copyright 2017 gorg
#include "symbolTable.hpp"
#include <string>


SymbolTable::SymbolTable() {}


void SymbolTable::pushSymbol(const Symbol sym) {
  this->symbolSet.back().insert(sym);
}

const Symbol *SymbolTable::findSymbol(Symbol sym) {
  Symbol *s = NULL;
  int i;

  for (i = this->symbolSet.size()-1; i >= 0; i--) {
    auto s = this->symbolSet[i].find(sym);
    if (s != this->symbolSet[i].end())
      return &*s;
  }

  return NULL;
}

bool SymbolTable::checkScope(Symbol sym) {
  return this->symbolSet.back().find(sym) != this->symbolSet.back().end();
}


bool SymbolTable::popSymbol(Symbol sym) {
  this->symbolSet.back().erase(sym);
  return true;
}

bool SymbolTable::enterScope() {
  std::set<Symbol> s;
  this->symbolSet.push_back(s);
  return true;
}

bool SymbolTable::exitScope() {
  this->symbolSet.pop_back();
  return true;
}
