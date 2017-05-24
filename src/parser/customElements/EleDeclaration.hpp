#ifndef ELEDECLARATION_H
#define ELEDECLARATION_H

#include "AstElement.hpp"


class SymbolTable;
class EleDeclaration : public AstElement
{
private:


public:

  bool preEleCompile(SymbolTable *s);

  EleDeclaration() : AstElement(AstStmtDeclaration) {};
  virtual ~EleDeclaration() {};
};

#endif /* ELEDECLARATION_H */
