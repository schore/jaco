#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "AstElementTree.h"
#include <vector>

class SymbolTable;
class AstElement : public AstElementTree
{
private:
protected:
  std::vector <AstElementTree *> leaves;
  ElementType type;
public:
  bool addLeave(AstElementTree *leave);
  void print(int ident = 0);

  void createTestStruct(std::vector <AstTestStruct> *testOutput,
                                int ident = 0);

  bool buildFuncSymbolTable(SymbolTable &s);
  bool compile(SymbolTable &s);


  AstElement(ElementType type) : type(type) {};
  virtual ~AstElement() {};
};

#endif /* ASTELEMENT_H */
