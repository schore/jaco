#ifndef ELESTMT_H
#define ELESTMT_H

#include "AstElement.hpp"

class EleStmt : public AstElement
{
private:
public:
  EleStmt() : AstElement(AstStmt) {};
  virtual ~EleStmt() {};
};

#endif /* ELESTMT_H */
