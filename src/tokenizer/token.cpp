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

Token::Token(eTokenType type) :
  type(type), dValue(0), intValue(0), str(0)
{}

Token::~Token() {
  if (this->str) delete str;
}

void Token::setStr(vector<char> vect) {
  int i;
  if (this->str) delete str;
  this->str = new char[vect.size()+1];

  for (i = 0; i < vect.size(); i++)
    this->str[i] = vect[i];

  this->str[vect.size()] = 0;
}
