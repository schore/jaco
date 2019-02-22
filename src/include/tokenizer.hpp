// copyright 2017 gorg
#ifndef SRC_INCLUDE_TOKENIZER_HPP_
#define SRC_INCLUDE_TOKENIZER_HPP_

#include <fstream>
#include <vector>

class Token;
class Tokenizer {
  bool isAllowedChar(char c);
  bool isOperator(char c);
  bool isBrace(char c);
  bool isSpecialChar(char c);
  bool isEmptySpace(char c);
  bool isEndOfSequence(char c);
  void removeSpace(std::ifstream *pFile);

  Token *createOperator(std::ifstream *pFile);
  Token *createNumber(std::ifstream *pFile);
  Token *createWord(std::ifstream *pFile);
  Token *createKeyword(std::ifstream *pFile);
  Token *createIdentifier(std::ifstream *pFile);
  Token *createBrace(std::ifstream *pFile);
  Token *createSpecialChar(std::ifstream *pFile);

  Token *parse(std::ifstream *pFile);

public:
  Tokenizer() {}
  std::vector<Token *> getAllTokens(std::ifstream *pFile);
};

#endif // SRC_INCLUDE_TOKENIZER_HPP_
