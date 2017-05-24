#include "token.hpp"

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
  type(type), dValue(0), intValue(0), str()
{}

Token::~Token() {
}

void Token::setStr(string str) {
  this->str = str;
}
