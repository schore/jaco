// copyright 2017 gorg
#ifndef SRC_INCLUDE_ASTPARSER_HPP_
#define SRC_INCLUDE_ASTPARSER_HPP_

#include <vector>
#include <token.hpp>
#include <AstElement.hpp>

class Token;
class AstParser {
  class Element {
   public:
      ElementType type;
      int parent;
      bool used;
      AstElementTree *el;
  };

  class InputStream {
   public:
      Token *tok;
      int parent;
      int pos;
  };

 private:
  std::vector <Element> node;
  std::vector <InputStream> inpStream;

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
  bool stmtWhile(int parent, bool newElement = true);
  bool stmtIf(int parent, bool newElement = true);
  bool stmtAssigment(int parent, bool newElement = true);
  bool stmtDeclaration(int parent, bool newElement = true);

  bool idList(int parent, bool newElement = true);
  bool parExpr(int parent, bool newElement = true);

  void cleanTree();
  void buildTree();

 public:
  bool parseToken(std::vector <Token*> inStream);

  AstElementTree *getRootNode();

  AstParser();
  virtual ~AstParser() {}
};

#endif  // SRC_INCLUDE_ASTPARSER_HPP_
