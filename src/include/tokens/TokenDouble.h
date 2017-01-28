#ifndef TOKEN_DOUBLE_H_
#define TOKEN_DOUBLE_H_

#include "../token.h"

class TokenDouble : public Token {
  double value;
  public:
  TokenDouble(double value) :
    Token(Token_Double), value(value) {};
};

#endif
