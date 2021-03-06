// Copyright 2017 gorg
#ifndef SRC_INCLUDE_ASTTERM_HPP_
#define SRC_INCLUDE_ASTTERM_HPP_

#include <memory>
#include <vector>

#include "AstElementTree.hpp"

class Token;
class AstTerm : public AstElementTree {
private:
  Token *pTok;

public:
  const Token *getPTok() { return this->pTok; }
  bool addLeave(AstElementTree *t) { return false; }

  void print(int ident = 0);
  void createTestStruct(std::vector<AstTestStruct> *testOutput, int ident = 0);

  explicit AstTerm(Token *pTok) { this->pTok = pTok; }
};

#endif // SRC_INCLUDE_ASTTERM_HPP_
