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

bool AstParser::stmt(int parent) {
  int par = this->addNode(AstFunc, parent);
  return true;
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
          &&  this->checkToken(Token_SwiftLeft, par)
          &&  this->stmt(par)
          &&  this->checkToken(Token_SwiftRight, par);
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
