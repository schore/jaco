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
  const TokenKeywordType type;
public:
  TokenKeyword(TokenKeywordType type) :
    Token(Token_Keyword), type(type) {};
};

#endif /* TOKENKEYWORD_H */
