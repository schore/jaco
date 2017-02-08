#include "AstTerm.h"
#include "token.h"

#include <iostream>

using namespace std;

void AstTerm::print(int ident) {

  for(int i=0; i < ident; i++) cout << "|  ";

  cout << "Term ";
  this->pTok->printToken();
}
