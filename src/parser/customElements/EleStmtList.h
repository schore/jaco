#ifndef ELESTMTLIST_H
#define ELESTMTLIST_H

#include "AstElementTree.h"

class EleStmtList : public AstElement
{
private:

public:
  EleStmtList() : AstElement(AstStmtList) {};
  virtual ~EleStmtList() {};
};

#endif /* ELESTMTLIST_H */
