#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"

#include "customElements/EleFunction.h"
#include "customElements/EleStmt.h"
#include "customElements/EleStmtList.h"
#include "customElements/EleDeclaration.h"

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
    default:
      return new AstElement(type);
  }
}
