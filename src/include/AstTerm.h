#ifndef ASTTERM_H
#define ASTTERM_H

#include "AstElementTree.h"

class Token;
class AstTerm : public AstElementTree
{
private:
  Token *pTok;

public:
  const Token *getPTok() const { return this->pTok; };
  bool addLeave(AstElementTree *t) {return false;}


  void print(int ident = 0);
  void createTestStruct(std::vector <AstTestStruct> &testOutput,
                                int ident = 0);


  AstTerm(Token *pTok) : pTok(pTok){};
  virtual ~AstTerm() {};
};

#endif /* ASTTERM_H */
