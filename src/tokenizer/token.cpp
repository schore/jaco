// copyright 2017 gorg
#include "token.hpp"

#include <iostream>

void Token::printToken() {
  const char *debugStrings[] = {
#define X(_STRING) # _STRING ,
    E_TOKEN_TYPE
#undef X
  };

  std::cout << debugStrings[this->type] << std::endl;
}

Token::Token(eTokenType type) :
  type(type), dValue(0), intValue(0), str()
{}

Token::~Token() {
}

void Token::setStr(std::string str) {
  this->str = str;
}
