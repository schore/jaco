// copyright 2017 gorg
#include "AstElement.h"
#include "AstElementTree.h"

#include <iostream>

bool AstElement::addLeave(AstElementTree *leave) {
  this->leaves.push_back(leave);
  return true;
}


void AstElement::print(int ident) {
  static const char * str[] = {
#define X(type) #type,
    AST_ELEMENT
#undef X
  };


  for ( auto i = 0; i < ident; i++ ) std::cout << "|  ";
  std::cout << str[this->type] << std::endl;

  ident++;

  for ( AstElementTree *e : this->leaves ) {
    e->print(ident);
  }
}


void AstElement::createTestStruct(std::vector<AstTestStruct> *output,
                                  int ident) {
  AstTestStruct t;
  t.isNode = true;
  t.nodes = ident;
  t.type = this->type;

  output->push_back(t);

  for ( AstElementTree *e : this->leaves ) {
    e->createTestStruct(output, ident+1);
  }
}

bool AstElement::buildFuncSymbolTable(SymbolTable &s) {
  bool ret;

  ret = this->buildEleFuncSymbolTable(s);

  for ( AstElementTree *l : this->leaves ) {
    ret &= l->buildFuncSymbolTable(s);
  }

  return ret;
}

bool AstElement::compile(SymbolTable &s) {
  bool ret;
  ret = this->preEleCompile(s);
  ret &= this->eleCompile(s);
  ret &= this->postEleCompile(s);
  for ( AstElementTree *l : this->leaves ) {
    ret &= l->compile(s);
  }
  return ret;
}


