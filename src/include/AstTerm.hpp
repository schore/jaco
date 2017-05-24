// Copyright 2017 gorg
#ifndef SRC_INCLUDE_ASTTERM_HPP_
#define SRC_INCLUDE_ASTTERM_HPP_

#include "AstElementTree.hpp"

#include <gsl/gsl>
#include <memory>
#include <vector>


class Token;
class AstTerm : public AstElementTree {
 private:
  gsl::owner<Token*> pTok;

 public:
  const Token *getPTok() { return this->pTok; }
  bool addLeave(AstElementTree *t) {return false;}


  void print(int ident = 0);
  void createTestStruct(std::vector <AstTestStruct> *testOutput,
                                int ident = 0);


  explicit AstTerm(gsl::owner<Token*> pTok) { this->pTok = pTok; }
  virtual ~AstTerm() {}
};

#endif  // SRC_INCLUDE_ASTTERM_HPP_
