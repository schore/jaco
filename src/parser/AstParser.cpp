#include "AstParser.h"
#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"

#include <iostream>

using namespace std;

AstParser::AstParser() : index(-1) {};

bool AstParser::checkToken(eTokenType type, int parent) {
  this->parent[this->index] = parent;
  return (type == this->inStream[this->index++]->getType());
}

bool AstParser::isNextToken(eTokenType type) {
  return (type == this->inStream[this->index]->getType());
}

int AstParser::addNode(ElementType type, int par, bool newElement) {
  Element e;
  e.type = type;
  e.parent = par;
  e.used = false;

  if (!newElement) return par;

  this->node.push_back(e);
  return this->parentIndex++;
}

bool AstParser::stmtList(int parent, bool newElement) {
  int par = this->addNode(AstStmtList, parent, newElement);
  int safe = this->index;
  return    (this->stmt(par)
          && this->stmtList(par, false))
      ||    (this->index = safe,
             this->stmt(par))
      ||    (this->index = safe,
             true);
}

bool AstParser::isMultToken(int parent) {
  int safe = this->index;
  return (this->index = safe, this->checkToken(Token_OperatorMultiply, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorDivide, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorModulo, parent))
          ;
}


bool AstParser::primary(int parent, bool newElement) {
  int par = this->addNode(AstPrimary, parent, newElement);
  int safe = this->index;
  return    (this->index = safe,
             this->checkToken(Token_Identifier, par))
      ||    (this->index = safe,
             this->checkToken(Token_Int, par))
      ||    (this->index = safe,
             this->checkToken(Token_Double, par))
      ||    (this->index = safe,
             this->checkToken(Token_BraceLeft, par)
         &&  this->expr(par)
         &&  this->checkToken(Token_BraceRight, par))
      ||    (this->index = safe,
             this->checkToken(Token_OperatorPlus, par)
         &&  this->primary(par))
      ||    (this->index = safe,
             this->checkToken(Token_OperatorMinus, par)
         &&  this->primary(par, false))
      ||    (this->index = safe,
             this->checkToken(Token_OperatorNot, par)
         &&  this->primary(par, false));
;
}



bool AstParser::mulExpr(int parent, bool newElement) {
  int par = this->addNode(AstMulExpr, parent, newElement);
  int safe = this->index;
  return     (this->primary(par)
           && this->isMultToken(par)
           && this->mulExpr(par, false))
        ||   (this->index = safe,
              this->primary(par));
}


bool AstParser::isAddToken(int parent) {
  int safe = this->index;
  return (this->index = safe, this->checkToken(Token_OperatorPlus, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorMinus, parent));
}

bool AstParser::addExpr(int parent, bool newElement) {
  int par = this->addNode(AstAddExpr, parent, newElement);
  int safe = this->index;
  return     (this->mulExpr(par)
           && this->isAddToken(par)
           && this->addExpr(par, false))
        ||   (this->index = safe,
              this->mulExpr(par));
}

bool AstParser::isEqualToken(int parent) {
  int safe = this->index;

  return (this->index = safe, this->checkToken(Token_OperatorEq, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorNEq, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorSmaller, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorSmallerEq, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorGreater, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorGreaterEq, parent));

}

bool AstParser::eqExpr(int parent, bool newElement) {
  int par = this->addNode(AstEqExpr, parent, newElement);
  int safe = this->index;
  return     (this->addExpr(par)
           && this->isEqualToken(par)
           && this->eqExpr(par, false))
        ||   (this->index = safe,
              this->addExpr(par));
}

bool AstParser::andExpr(int parent, bool newElement) {
  int par = this->addNode(AstAndExpr, parent, newElement);
  int safe = this->index;
  return     (this->eqExpr(par)
           && this->checkToken(Token_OperatorLogicAnd, par)
           && this->andExpr(par, false))
        ||   (this->index = safe,
              this->eqExpr(par));
}

bool AstParser::expr(int parent, bool newElement) {
  int par = this->addNode(AstExpr, parent, newElement);
  int safe = this->index;
  return     (this->andExpr(par)
           && this->checkToken(Token_OperatorLogicOr, par)
           && this->expr(par, false))
        ||   (this->index = safe,
              this->andExpr(par));
}

bool AstParser::parExpr(int parent, bool newElement) {
  int par = this->addNode(AstParExpr, parent, newElement);
  int safe = this->index;
  return    this->checkToken(Token_BraceLeft, par)
         && this->expr(par)
         && this->checkToken(Token_BraceRight, par);
}


bool AstParser::stmtWhile(int parent, bool newElement) {
  int par = this->addNode(AstStmtWhile, parent, newElement);
  int safe = this->index;

  return      (this->index = safe,
               this->checkToken(Token_KeywordWhile, par)
           &&  this->parExpr(par)
           &&  this->stmt(par));
}



bool AstParser::stmtIf(int parent, bool newElement) {
  int par = this->addNode(AstStmtIf, parent, newElement);
  int safe = this->index;

  return      (this->index = safe,
               this->checkToken(Token_KeywordIf, par)
           &&  this->parExpr(par)
           &&  this->stmt(par)
           &&  this->checkToken(Token_KeywordElse, par)
           &&  this->stmt(par))
         ||   (this->index = safe,
               this->checkToken(Token_KeywordIf, par)
           &&  this->parExpr(par)
           &&  this->stmt(par));
}


bool AstParser::stmtDeclaration(int parent, bool newElement) {
  int par = this->addNode(AstStmtDeclaration, parent, newElement);
  int safe = this->index;

  return      (this->index = safe,
               this->checkToken(Token_KeywordVar, par)
           &&  this->checkToken(Token_Identifier, par)
           &&  this->checkToken(Token_OperatorAssign, par)
           &&  this->expr(par)
           &&  this->checkToken(Token_Semilicon, par))
         ||   (this->index = safe,
               this->checkToken(Token_KeywordVar, par)
           &&  this->checkToken(Token_Identifier, par)
           &&  this->checkToken(Token_Semilicon, par));
}



bool AstParser::stmtAssigment(int parent, bool newElement) {
  int par = this->addNode(AstStmtAssignment, parent, newElement);
  int safe = this->index;
  return      (this->index = safe,
               this->checkToken(Token_Identifier, par)
           &&  this->checkToken(Token_OperatorEq, par)
           &&  this->expr(par)
           &&  this->checkToken(Token_Semilicon, par));

}



bool AstParser::stmt(int parent, bool newElement) {
  int par = this->addNode(AstStmt, parent, newElement);
  int safe = this->index;

  return      (this->index = safe,
               this->checkToken(Token_Semilicon, par))
         ||   (this->index = safe,
               this->checkToken(Token_SwiftLeft, par)
           &&  this->stmtList(par)
           &&  this->checkToken(Token_SwiftRight, par))
         ||   (this->index = safe,
               this->stmtAssigment(par))
         ||   (this->index = safe,
               this->stmtWhile(par))
         ||   (this->index = safe,
               this->stmtIf(par))
         ||   (this->index = safe,
               this->stmtDeclaration(par));
}

bool AstParser::idList(int parent, bool newElement) {
  int par = this->addNode(AstIdList, parent, newElement);
  int safe = this->index;

  return       this->isNextToken(Token_BraceRight)
         ||(   this->checkToken(Token_Identifier, par)
            && this->isNextToken(Token_BraceRight))
         ||((  this->index = safe,
               this->checkToken(Token_Identifier, par)
            && this->idList(par, false)))
         ||((  this->index = safe,
               this->checkToken(Token_Comma, par)
            && this->checkToken(Token_Identifier, par)
            && this->idList(par, false)));
}

bool AstParser::func(int parent, bool newElement) {
  int par = this->addNode(AstFunc, parent, newElement);
  int safe = this->index;
  bool ret =  this->checkToken(Token_KeywordFunc, par)
          &&  this->checkToken(Token_Identifier, par)
          &&  this->checkToken(Token_BraceLeft, par)
          &&  this->idList(par)
          &&  this->checkToken(Token_BraceRight, par)
          &&  this->stmt(par);
}

bool AstParser::root(int parent, bool newElement) {
  int par = this->addNode(AstRoot, parent, newElement);
  int safe = this->index;
  return (   this->checkToken(Token_Eof, par)
          || (this->index = safe,
              this->func(par) && this->root(par, false)));

}

void AstParser::cleanTree() {
  int par;
  for (int n : this->parent) {
    par = n;
    while ( par > 0) {
      this->node[par].used = true;
      par = this->node[par].parent;
    }
  }
}

void AstParser::buildTree() {
  for ( Element &n : this->node) {
    if (n.used) {
      n.el = new AstElement(n.type);
      if (n.parent > 0) {
        this->node[n.parent].el->addLeave(n.el);
      }
    }
  }

  for ( int i = 0; i < this->inStream.size(); i++) {
    AstTerm *t = new AstTerm(this->inStream[i]);
    this->node[this->parent[i]].el->addLeave(t);
  }
}

bool AstParser::parseToken(vector <Token *> inStream) {
  this->inStream = inStream;
  this->index = 0;
  this->parentIndex = 0;
  this->parent.resize(inStream.size(), 0);

  int par = this->addNode(AstEntry, 1, true);

  this->root(par);
  this->cleanTree();
  this->buildTree();

  this->node[1].el->print();

  return false;
}


