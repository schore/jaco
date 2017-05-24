#ifndef ELEFUNCTION_H
#define ELEFUNCTION_H

#include "AstElement.hpp"

class EleFunction : public AstElement
{
private:
   bool buildEleFuncSymbolTable(SymbolTable &s);

public:
  EleFunction() : AstElement(AstFunc) {};
  virtual ~EleFunction() {};
};

#endif /* ELEFUNCTION_H */
