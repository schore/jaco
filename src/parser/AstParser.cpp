#include "AstParser.h"
#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"

#include <iostream>

using namespace std;

AstParser::AstParser() : index(-1) {};

bool AstParser::checkToken(eTokenType type, int parent) {
  cout << "Consumed " << this->index << " " << parent << " ";
  this->parent[this->index] = parent;
  this->inStream[this->index]->printToken();
  return (type == this->inStream[this->index++]->getType());
}

bool AstParser::isNextToken(eTokenType type) {
  return (type == this->inStream[this->index]->getType());
}

int AstParser::addNode(ElementType type, int par) {
  Element e;
  e.type = type;
  e.parent = par;

  this->node.push_back(e);
  return this->parentIndex++;
}

bool AstParser::stmtList(int parent) {
  int par = this->addNode(AstStmtList, parent);
  int safe = this->index;
  return    (this->stmt(par)
          && this->stmtList(par))
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


bool AstParser::primary(int parent) {
  int par = this->addNode(AstPrimary, parent);
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
         &&  this->primary(par))
      ||    (this->index = safe,
             this->checkToken(Token_OperatorNot, par)
         &&  this->primary(par));
;
}



bool AstParser::mulExpr(int parent) {
  int par = this->addNode(AstMulExpr, parent);
  int safe = this->index;
  return     (this->primary(par)
           && this->isMultToken(par)
           && this->mulExpr(par))
        ||   (this->index = safe,
              this->primary(par));
}


bool AstParser::isAddToken(int parent) {
  int safe = this->index;
  return (this->index = safe, this->checkToken(Token_OperatorPlus, parent))
    ||   (this->index = safe, this->checkToken(Token_OperatorMinus, parent));
}

bool AstParser::addExpr(int parent) {
  int par = this->addNode(AstAddExpr, parent);
  int safe = this->index;
  return     (this->mulExpr(par)
           && this->isAddToken(par)
           && this->addExpr(par))
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

bool AstParser::eqExpr(int parent) {
  int par = this->addNode(AstEqExpr, parent);
  int safe = this->index;
  return     (this->addExpr(par)
           && this->isEqualToken(par)
           && this->eqExpr(par))
        ||   (this->index = safe,
              this->addExpr(par));
}

bool AstParser::andExpr(int parent) {
  int par = this->addNode(AstAndExpr, parent);
  int safe = this->index;
  return     (this->eqExpr(par)
           && this->checkToken(Token_OperatorLogicAnd, par)
           && this->andExpr(par))
        ||   (this->index = safe,
              this->eqExpr(par));
}

bool AstParser::expr(int parent) {
  int par = this->addNode(AstExpr, parent);
  int safe = this->index;
  return     (this->andExpr(par)
           && this->checkToken(Token_OperatorLogicOr, par)
           && this->expr(par))
        ||   (this->index = safe,
              this->andExpr(par));
}

bool AstParser::parExpr(int parent) {
  int par = this->addNode(AstParExpr, parent);
  int safe = this->index;
  return    this->checkToken(Token_BraceLeft, par)
         && this->expr(par)
         && this->checkToken(Token_BraceRight, par);
}

bool AstParser::stmt(int parent) {
  int par = this->addNode(AstFunc, parent);
  int safe = this->index;

  return      (this->index = safe,
               this->checkToken(Token_Semilicon, par))
         ||   (this->index = safe,
               this->checkToken(Token_SwiftLeft, par)
           &&  this->stmtList(par)
           &&  this->checkToken(Token_SwiftRight, par))
         ||   (this->index = safe,
               this->checkToken(Token_Identifier, par)
           &&  this->checkToken(Token_OperatorEq, par)
           &&  this->expr(par)
           &&  this->checkToken(Token_Semilicon, par))
         ||   (this->index = safe,
               this->checkToken(Token_KeywordWhile, par)
           &&  this->parExpr(par)
           &&  this->stmt(parent))
         ||   (this->index = safe,
               this->checkToken(Token_KeywordIf, par)
           &&  this->parExpr(par)
           &&  this->stmt(par)
           &&  this->checkToken(Token_KeywordElse, par)
           &&  this->stmt(par))
         ||   (this->index = safe,
               this->checkToken(Token_KeywordIf, par)
           &&  this->parExpr(par)
           &&  this->stmt(par))
         ||   (this->index = safe,
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

bool AstParser::idList(int parent) {
  int par = this->addNode(AstIdList, parent);
  int safe = this->index;
  bool ret = false;

  return       this->isNextToken(Token_BraceRight)
         ||(   this->checkToken(Token_Identifier, par)
            && this->isNextToken(Token_BraceRight))
         ||((  this->index = safe,
               this->checkToken(Token_Identifier, par)
            && this->idList(par)))
         ||((  this->index = safe,
               this->checkToken(Token_Comma, par)
            && this->checkToken(Token_Identifier, par)
            && this->idList(par)));
}

bool AstParser::func(int parent) {
  int par = this->addNode(AstFunc, parent);
  int safe = this->index;
  bool ret =  this->checkToken(Token_KeywordFunc, par)
          &&  this->checkToken(Token_Identifier, par)
          &&  this->checkToken(Token_BraceLeft, par)
          &&  this->idList(par)
          &&  this->checkToken(Token_BraceRight, par)
          &&  this->stmt(par);
}

bool AstParser::root(int parent) {
  int par = this->addNode(AstRoot, parent);
  int safe = this->index;
  return (   this->checkToken(Token_Eof, par)
          || (this->index = safe,
              this->func(par) && this->root(par)));

}

bool AstParser::parseToken(vector <Token *> inStream) {
  this->inStream = inStream;
  this->index = 0;
  this->parentIndex = 0;
  this->parent.resize(inStream.size(), 0);

  int par = this->addNode(AstEntry, -1);

  this->root(par);

  for ( Element n : this->node) {
   cout << n.type << " " << n.parent << endl;
  }

  cout << endl;

  int i;
  for ( int j : parent) {
    cout << i++ << " " << j << endl;
  }

  return false;
}
