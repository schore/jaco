// copyright 2017 gorg
#ifndef SRC_INCLUDE_ASTELEMENTTREE_HPP_
#define SRC_INCLUDE_ASTELEMENTTREE_HPP_

#include <vector>

#define AST_ELEMENT                                                            \
  X(AstEntry)                                                                  \
  X(AstRoot)                                                                   \
  X(AstFunc)                                                                   \
  X(AstStmt)                                                                   \
  X(AstStmtWhile)                                                              \
  X(AstStmtIf)                                                                 \
  X(AstStmtDeclaration)                                                        \
  X(AstStmtAssignment)                                                         \
  X(AstIdList)                                                                 \
  X(AstStmtList)                                                               \
  X(AstExpr)                                                                   \
  X(AstParExpr)                                                                \
  X(AstAndExpr)                                                                \
  X(AstPrimary)                                                                \
  X(AstMulExpr)                                                                \
  X(AstAddExpr)                                                                \
  X(AstEqExpr)

enum ElementType {
#define X(type) type,
  AST_ELEMENT
#undef X
};

struct AstTestStruct {
  int nodes;
  int type;
  bool isNode;
};

class Token;
class SymbolTable;
class AstElementTree {
public:
  virtual void print(int ident = 0) = 0;
  virtual void createTestStruct(std::vector<AstTestStruct> *testOutput,
                                int ident = 0) = 0;

  virtual bool buildEleFuncSymbolTable(SymbolTable *s) { return true; }
  virtual bool buildFuncSymbolTable(SymbolTable *s) { return true; }

  virtual bool preEleCompile(SymbolTable *s) { return true; }

  virtual bool compile(SymbolTable *s) { return true; }
  virtual bool eleCompile(SymbolTable *s) { return true; }

  virtual bool postEleCompile(SymbolTable *s) { return true; }

  virtual bool addLeave(AstElementTree *t) = 0;

  static AstElementTree *createElement(ElementType type);
  static AstElementTree *createElement(Token *tok);

  AstElementTree() {}
};

#endif // SRC_INCLUDE_ASTELEMENTTREE_HPP_
