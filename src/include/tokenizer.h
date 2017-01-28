#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <iostream>

class Token;
class Tokenizer
{
  public:
    Tokenizer() {};
    static Token *getAllTokens(FILE *pFile);
};

#endif
