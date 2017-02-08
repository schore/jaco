#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "AstElementTree.h"
#include <vector>

#define AST_ELEMENT\
  X(AstEntry)\
  X(AstRoot)\
  X(AstFunc)\
  X(AstStmt)\
  X(AstStmtWhile)\
  X(AstStmtIf)\
  X(AstStmtDeclaration)\
  X(AstStmtAssignment)\
  X(AstIdList)\
  X(AstStmtList)\
  X(AstExpr)\
  X(AstParExpr)\
  X(AstAndExpr)\
  X(AstPrimary)\
  X(AstMulExpr)\
  X(AstAddExpr)\
  X(AstEqExpr)\

enum ElementType {
#define X(type) type,
  AST_ELEMENT
#undef X
};


class AstElement : public AstElementTree
{
private:
  std::vector <AstElementTree *> leaves;
  ElementType type;

public:
  void addLeave(AstElementTree *leave);
  void print(int ident = 0);

  AstElement(ElementType type) : type(type) {};
  virtual ~AstElement() {};
};

#endif /* ASTELEMENT_H */
