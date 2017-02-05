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

  int addNode(ElementType type, int par);

  bool checkToken(eTokenType type, int parent);
  bool isNextToken(eTokenType type);

  bool isEqualToken(int parent);
  bool isAddToken(int parent);
  bool isMultToken(int parent);



  bool expr(int parent);
  bool andExpr(int parent);
  bool eqExpr(int parent);
  bool addExpr(int parent);
  bool mulExpr(int parent);
  bool primary(int parent);
  bool root(int parent);
  bool func(int parent);
  bool stmt(int parent);
  bool stmtList(int parent);
  bool idList(int parent);
  bool parExpr(int parent);
public:
  bool parseToken(std::vector <Token*> inStream);

  AstParser();
  virtual ~AstParser() {};
};

#endif /* ASTPARSER_H */
