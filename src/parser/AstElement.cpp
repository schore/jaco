#include "AstElement.h"
#include "AstElementTree.h"

#include <iostream>

using namespace std;

bool AstElement::addLeave(AstElementTree *leave) {
  this->leaves.push_back(leave);
  return true;
}


void AstElement::print(int ident) {
  const static char * str[] = {
#define X(type) #type,
    AST_ELEMENT
#undef X
  };


  for(int i=0; i < ident; i++) cout << "|  ";
  cout << str[this->type] << endl;

  ident++;

  for( AstElementTree *e : this->leaves) {
    e->print(ident);
  }
}


void AstElement::createTestStruct(vector<AstTestStruct> &output, int ident) {
  AstTestStruct t;
  t.isNode = true;
  t.nodes = ident;
  t.type = this->type;

  output.push_back(t);

  for( AstElementTree *e : this->leaves) {
    e->createTestStruct(output, ident+1);
  }
}

bool AstElement::buildFuncSymbolTable(SymbolTable &s) {

  bool ret;

  ret = this->buildEleFuncSymbolTable(s);

  for ( AstElementTree *l : this->leaves) {
    ret &= l->buildFuncSymbolTable(s);
  }

  return ret;
}

bool AstElement::preCompile(SymbolTable &s) {
  bool ret;
  ret = this->preEleCompile(s);
  for(AstElementTree *l : this->leaves) {
    ret &= l->preCompile(s);
  }
  return ret;
}

bool AstElement::compile(SymbolTable &s) {
  bool ret;
  ret = this->eleCompile(s);
  for(AstElementTree *l : this->leaves) {
    ret &= l->compile(s);
  }
  return ret;
}

bool AstElement::postCompile(SymbolTable &s) {
  bool ret;
  ret = this->postEleCompile(s);
  for(AstElementTree *l : this->leaves) {
    ret &= l->postCompile(s);
  }
  return ret;
}

