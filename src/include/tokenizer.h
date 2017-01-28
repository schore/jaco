#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <iostream>
#include <vector>

class Token;
class Tokenizer
{
    Token *parse(FILE *pFile);
  public:
    Tokenizer() {};
    std::vector<Token *> getAllTokens(FILE *pFile);
};

#endif
