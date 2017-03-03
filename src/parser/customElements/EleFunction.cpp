#include "EleFunction.h"
#include "symbolTable.h"
#include "AstTerm.h"
#include "token.h"

#include <iostream>


using namespace std;

bool EleFunction::buildEleFuncSymbolTable(SymbolTable &symTable) {
  AstTerm *ident = (AstTerm *)this->leaves[1];
  const Token &t = *ident->getPTok();
  Symbol s;

  s.str = t.getString();

  if(symTable.findSymbol(s)) return false;

  cout << "Function " << t.getString() << endl;

  symTable.pushSymbol(s);
  return true;
}
