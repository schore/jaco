// copyright 2017 gorg
#ifndef SRC_PARSER_CUSTOMELEMENTS_ELEFUNCTION_HPP_
#define SRC_PARSER_CUSTOMELEMENTS_ELEFUNCTION_HPP_

#include "AstElement.hpp"

class EleFunction : public AstElement {
private:
  bool buildEleFuncSymbolTable(SymbolTable *s);

public:
  EleFunction() : AstElement(AstFunc) {}
  virtual ~EleFunction() {}
};

#endif // SRC_PARSER_CUSTOMELEMENTS_ELEFUNCTION_HPP_
