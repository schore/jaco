// copyright 2017 gorg
#include "EleStmtList.hpp"

#include "symbolTable.hpp"

bool EleStmtList::preEleCompile(SymbolTable *s) { return s->enterScope(); }

bool EleStmtList::postEleCompile(SymbolTable *s) { return s->exitScope(); }
