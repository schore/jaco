// copyright 2017 gorg
#ifndef SRC_PARSER_CUSTOMELEMENTS_ELEEXPR_HPP_
#define SRC_PARSER_CUSTOMELEMENTS_ELEEXPR_HPP_

#include "AstElement.hpp"

class EleExpr : public AstElement {
 private:
  bool compile(SymbolTable *s);
 public:
  EleExpr() : AstElement(AstExpr) {}
  virtual ~EleExpr() {}
};

#endif  // SRC_PARSER_CUSTOMELEMENTS_ELEEXPR_HPP_
