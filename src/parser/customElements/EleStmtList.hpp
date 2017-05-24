#ifndef ELESTMTLIST_H
#define ELESTMTLIST_H

#include "AstElement.hpp"

class SymbolTable;
class EleStmtList : public AstElement
{
private:
protected:

public:
  bool preEleCompile(SymbolTable &s);
  bool postEleCompile(SymbolTable &s);

 EleStmtList() : AstElement(AstStmtList) {};
  virtual ~EleStmtList() {};
};

#endif /* ELESTMTLIST_H */
