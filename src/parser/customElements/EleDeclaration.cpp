#include "EleDeclaration.h"

#include "token.h"
#include "symbolTable.h"
#include "AstTerm.h"

#include "debug_helper.h"

bool EleDeclaration::preEleCompile(SymbolTable &s) {
  const Token *iden = (( AstTerm *) this->leaves[1])->getPTok();
  Symbol sym;
  sym.str = iden->getString();

  ASSERT(!s.checkScope(sym), false);
  s.pushSymbol(sym);

  return true;
}
