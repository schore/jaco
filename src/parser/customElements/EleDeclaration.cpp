// copyright 2017 gorg
#include "EleDeclaration.hpp"

#include <debug_helper.h>

#include "AstTerm.hpp"
#include "symbolTable.hpp"
#include "token.hpp"

bool EleDeclaration::preEleCompile(SymbolTable *s) {
  const Token *iden = dynamic_cast<AstTerm *>(this->leaves[1])->getPTok();
  Symbol sym;
  sym.str = iden->getString();

  ASSERT(!s->checkScope(sym), false);
  s->pushSymbol(sym);

  return true;
}
