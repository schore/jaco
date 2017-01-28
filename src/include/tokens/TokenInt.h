#ifndef TOKEN_INT_H_
#define TOKEN_INT_H_

#include "../token.h"

class TokenInt : public Token {
  long int value;
  public:
  TokenInt(long int value) :
    Token(Token_Int), value(value) {};
};

#endif
