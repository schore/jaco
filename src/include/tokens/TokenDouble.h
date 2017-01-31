#ifndef TOKEN_DOUBLE_H_
#define TOKEN_DOUBLE_H_

#include "../token.h"

class TokenDouble : public Token {
  double value;
  public:
  double getValue() { return this->value; }
  TokenDouble(double value) :
    Token(Token_Double), value(value) {};
};

#endif
