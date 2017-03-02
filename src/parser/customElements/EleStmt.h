#ifndef ELESTMT_H
#define ELESTMT_H

#include "AstElement.h"

class EleStmt : public AstElement
{
private:
public:
  EleStmt() : AstElement(AstStmt) {};
  virtual ~EleStmt() {};
};

#endif /* ELESTMT_H */
