#include "EleDeclaration.hpp"

#include "token.hpp"
#include "symbolTable.hpp"
#include "AstTerm.hpp"

#include "debug_helper.h"

bool EleDeclaration::preEleCompile(SymbolTable *s) {
  const Token *iden = (( AstTerm *) this->leaves[1])->getPTok();
  Symbol sym;
  sym.str = iden->getString();

  ASSERT(!s->checkScope(sym), false);
  s->pushSymbol(sym);

  return true;
}
