#include "AstTerm.h"
#include "token.h"

#include <iostream>

using namespace std;

void AstTerm::print(int ident) {

  for(int i=0; i < ident; i++) cout << "|  ";

  cout << "Term ";
  this->pTok->printToken();
}


void AstTerm::createTestStruct(vector <AstTestStruct> &output, int ident) {
  AstTestStruct t;
  t.isNode = false;
  t.nodes = ident;
  t.type = this->pTok->getType();
  output.push_back(t);
}

