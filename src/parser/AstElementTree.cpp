#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"


AstElementTree *AstElementTree::createElement(Token *t) {
  return new AstTerm(t);
}

AstElementTree *AstElementTree::createElement(ElementType type) {
  return new AstElement(type);
}
