#include "token.h"

#include <iostream>

using namespace std;


void Token::printToken() {
  const char *debugStrings[] = {
#define X(_STRING) # _STRING ,
    E_TOKEN_TYPE
#undef X
  };

  cout << debugStrings[this->type] << endl;
}
