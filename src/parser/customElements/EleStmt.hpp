// copyright 2017 gorg
#ifndef SRC_PARSER_CUSTOMELEMENTS_ELESTMT_HPP_
#define SRC_PARSER_CUSTOMELEMENTS_ELESTMT_HPP_

#include "AstElement.hpp"

class EleStmt : public AstElement {
public:
  EleStmt() : AstElement(AstStmt) {}
  virtual ~EleStmt() {}
};

#endif // SRC_PARSER_CUSTOMELEMENTS_ELESTMT_HPP_
