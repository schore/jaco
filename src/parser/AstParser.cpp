#include "AstParser.h"
#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"

#include <iostream>




using namespace std;

AstParser::AstParser() : index(-1) {};

bool AstParser::checkToken(eTokenType type) {
  cout << "Consumed " << this->index << " ";
  this->inStream[this->index]->printToken();
  return (type == this->inStream[this->index++]->getType());
}

bool AstParser::isNextToken(eTokenType type) {
  return (type == this->inStream[this->index]->getType());
}


bool AstParser::stmt() {
  return true;
}

bool AstParser::idList() {
  int safe = this->index;
  bool ret = false;

  return       this->isNextToken(Token_BraceRight)
         ||(   this->checkToken(Token_Identifier)
            && this->isNextToken(Token_BraceRight))
         ||((  this->index = safe,
               this->checkToken(Token_Identifier)
            && this->idList()))
         ||((  this->index = safe,
               this->checkToken(Token_Comma)
            && this->checkToken(Token_Identifier)
            && this->idList()));
}

bool AstParser::func() {
  int safe = this->index;
  bool ret =  this->checkToken(Token_KeywordFunc)
          &&  this->checkToken(Token_Identifier)
          &&  this->checkToken(Token_BraceLeft)
          &&  this->idList()
          &&  this->checkToken(Token_BraceRight)
          &&  this->checkToken(Token_SwiftLeft)
          &&  this->stmt()
          &&  this->checkToken(Token_SwiftRight);
}

bool AstParser::root() {
  int safe = this->index;
  return (   this->checkToken(Token_Eof)
          || (this->index = safe,
              this->func() && this->root()));

}

bool AstParser::parseToken(vector <Token *> inStream) {
  this->inStream = inStream;
  this->index = 0;

  this->root();
  return false;
}
