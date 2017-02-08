#include "AstElement.h"

#include <iostream>

using namespace std;

void AstElement::addLeave(AstElementTree *leave) {
  this->leaves.push_back(leave);
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


