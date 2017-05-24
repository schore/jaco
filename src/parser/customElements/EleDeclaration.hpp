// copyright 2017 gorg
#ifndef SRC_PARSER_CUSTOMELEMENTS_ELEDECLARATION_HPP_
#define SRC_PARSER_CUSTOMELEMENTS_ELEDECLARATION_HPP_

#include "AstElement.hpp"


class SymbolTable;
class EleDeclaration : public AstElement {
 public:
  bool preEleCompile(SymbolTable *s);

  EleDeclaration() : AstElement(AstStmtDeclaration) {}
  virtual ~EleDeclaration() {}
};

#endif  // SRC_PARSER_CUSTOMELEMENTS_ELEDECLARATION_HPP_
