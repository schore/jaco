// copyright 2017 gorg
#ifndef SRC_PARSER_CUSTOMELEMENTS_ELESTMTLIST_HPP_
#define SRC_PARSER_CUSTOMELEMENTS_ELESTMTLIST_HPP_

#include "AstElement.hpp"

class SymbolTable;
class EleStmtList : public AstElement {
public:
  bool preEleCompile(SymbolTable *s);
  bool postEleCompile(SymbolTable *s);

  EleStmtList() : AstElement(AstStmtList) {}
  virtual ~EleStmtList() {}
};

#endif // SRC_PARSER_CUSTOMELEMENTS_ELESTMTLIST_HPP_
