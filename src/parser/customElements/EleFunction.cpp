// copyright 2017 gorg
#include "EleFunction.hpp"

#include <iostream>

#include "symbolTable.hpp"
#include "AstTerm.hpp"
#include "token.hpp"



bool EleFunction::buildEleFuncSymbolTable(SymbolTable *symTable) {
  AstTerm *ident = dynamic_cast<AstTerm *>(this->leaves[1]);
  const Token &t = *ident->getPTok();
  Symbol s;

  s.str = t.getString();

  if (symTable->findSymbol(s)) return false;

  std::cout << "Function " << t.getString() << std::endl;

  symTable->pushSymbol(s);
  return true;
}
