#ifndef ELEEXPR_H
#define ELEEXPR_H

#include "AstElement.h"

class EleExpr : public AstElement
{
private:
  bool compile(SymbolTable &s);
public:
  EleExpr() : AstElement(AstExpr) {};
  virtual ~EleExpr() {};
};

#endif /* ELEEXPR_H */
