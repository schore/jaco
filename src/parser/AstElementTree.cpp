#include "AstElementTree.hpp"
#include "AstElement.hpp"
#include "AstTerm.hpp"

#include "customElements/EleFunction.hpp"
#include "customElements/EleStmt.hpp"
#include "customElements/EleStmtList.hpp"
#include "customElements/EleDeclaration.hpp"
#include "customElements/EleExpr.hpp"

AstElementTree *AstElementTree::createElement(Token *t) {
  return new AstTerm(t);
}

AstElementTree *AstElementTree::createElement(ElementType type) {
  switch(type) {
    case AstFunc:
      return new EleFunction;
    case AstStmt:
      return new EleStmt;
    case AstStmtList:
      return new EleStmtList;
    case AstStmtDeclaration:
      return new EleDeclaration;
    case AstExpr:
      return new EleExpr;
    default:
      return new AstElement(type);
  }
}
