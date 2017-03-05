#include "EleStmtList.h"

#include "symbolTable.h"

bool EleStmtList::preEleCompile(SymbolTable &s) {
  return s.enterScope();
}

bool EleStmtList::postEleCompile(SymbolTable &s) {
  return s.exitScope();
}
