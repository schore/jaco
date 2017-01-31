#ifndef TOKENKEYWORD_H
#define TOKENKEYWORD_H

#include "../token.h"


enum TokenKeywordType {
  TokenKeywordIf,
  TokenKeywordElse,
  TokenKeywordWhile,
  TokenKeywordFor,
};

class TokenKeyword : public Token
{
  const TokenKeywordType tokType;
public:
  TokenKeywordType getKeywordType() { return this->tokType; }

  TokenKeyword(TokenKeywordType type) :
    Token(Token_Keyword), tokType(type) {};
};

#endif /* TOKENKEYWORD_H */
