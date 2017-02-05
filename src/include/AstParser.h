#ifndef ASTPARSER_H
#define ASTPARSER_H

#include <vector>
#include "token.h"
#include "AstElement.h"


class Token;
class AstParser
{
private:
  std::vector <Token *> inStream;
  int index;

  bool checkToken(eTokenType type);
  bool isNextToken(eTokenType type);

  bool root();
  bool func();
  bool stmt();
  bool idList();
public:
  bool parseToken(std::vector <Token*> inStream);

  AstParser();
  virtual ~AstParser() {};
};

#endif /* ASTPARSER_H */
