#ifndef ASTPARSER_H
#define ASTPARSER_H

#include <vector>
#include "token.h"
#include "AstElement.h"

class Token;
class AstParser
{
  enum ElementType {
    AstEntry,
    AstRoot,
    AstFunc,
    AstStmt,
    AstIdList,
  };

  struct Element {
    ElementType type;
    int parent;
  };

private:
  std::vector <Token *> inStream;
  std::vector <int> parent;
  std::vector <Element> node;

  int index;
  int parentIndex;

  int addNode(ElementType type, int par);

  bool checkToken(eTokenType type, int parent);
  bool isNextToken(eTokenType type);

  bool root(int parent);
  bool func(int parent);
  bool stmt(int parent);
  bool idList(int parent);
public:
  bool parseToken(std::vector <Token*> inStream);

  AstParser();
  virtual ~AstParser() {};
};

#endif /* ASTPARSER_H */
