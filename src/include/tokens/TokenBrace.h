#ifndef TOKEN_BRACE_H_
#define TOKEN_BRACE_H_

#include "../token.h"

enum TokenBraceType {
  TokBraceLeftRound,
  TokBraceRightRound,
  TokBraceLeftSwift,
  TokBraceRightSwift,
};

class TokenBrace : public Token {
  TokenBraceType braceType;
  public:
  TokenBrace(TokenBraceType braceType) :
    Token(Token_Double), braceType(braceType) {};
};

#endif
