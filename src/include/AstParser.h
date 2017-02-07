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
    AstStmtList,
    AstExpr,
    AstParExpr,
    AstAndExpr,
    AstPrimary,
    AstMulExpr,
    AstAddExpr,
    AstEqExpr,
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

  int addNode(ElementType type, int par, bool newElement);

  bool checkToken(eTokenType type, int parent);
  bool isNextToken(eTokenType type);

  bool isEqualToken(int parent);
  bool isAddToken(int parent);
  bool isMultToken(int parent);
  bool isAssign(int parent);



  bool expr(int parent, bool newElement = true);
  bool andExpr(int parent, bool newElement = true);
  bool eqExpr(int parent, bool newElement = true);
  bool addExpr(int parent, bool newElement = true);
  bool mulExpr(int parent, bool newElement = true);
  bool primary(int parent, bool newElement = true);
  bool root(int parent, bool newElement = true);
  bool func(int parent, bool newElement = true);
  bool stmt(int parent, bool newElement = true);
  bool stmtList(int parent, bool newElement = true);
  bool idList(int parent, bool newElement = true);
  bool parExpr(int parent, bool newElement = true);
public:
  bool parseToken(std::vector <Token*> inStream);

  AstParser();
  virtual ~AstParser() {};
};

#endif /* ASTPARSER_H */
