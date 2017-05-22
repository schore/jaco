#ifndef ASTTERM_H
#define ASTTERM_H

#include "AstElementTree.h"
#include <memory>
#include <gsl/gsl>


class Token;
class AstTerm : public AstElementTree
{
private:
  gsl::owner<Token*> pTok = nullptr;

public:
  const Token *getPTok() { return this->pTok; };
  bool addLeave(AstElementTree *t) {return false;}


  void print(int ident = 0);
  void createTestStruct(std::vector <AstTestStruct> &testOutput,
                                int ident = 0);


  AstTerm(gsl::owner<Token*> pTok) {this->pTok = pTok; };
  virtual ~AstTerm() {};
};

#endif /* ASTTERM_H */
