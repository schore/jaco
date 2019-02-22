// copyright 2017 gorg
#include "AstTerm.hpp"

#include <iostream>

#include "token.hpp"

void AstTerm::print(int ident) {
  for (int i = 0; i < ident; i++)
    std::cout << "|  ";

  std::cout << "Term ";
  this->pTok->printToken();
}

void AstTerm::createTestStruct(std::vector<AstTestStruct> *output, int ident) {
  AstTestStruct t = {};
  t.isNode = false;
  t.type = this->pTok->getType();
  t.nodes = ident;

  output->push_back(t);
}
