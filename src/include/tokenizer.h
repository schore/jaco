#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <fstream>
#include <vector>

class Token;
class Tokenizer
{
    bool isAllowedChar(char c);
    bool isOperator(char c);
    bool isBrace(char c);
    void removeSpace(std::ifstream *pFile);

    Token *createOperator(std::ifstream *pFile);
    Token *createNumber(std::ifstream *pFile);
    Token *createWord(std::ifstream *pFile);
    Token *createBrace(std::ifstream *pFile);

    Token *parse(std::ifstream *pFile);
  public:
    Tokenizer() {};
    std::vector<Token *> getAllTokens(std::ifstream *pFile);
};

#endif
