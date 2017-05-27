// copyright 2017 gorg
#ifndef SRC_INCLUDE_ASTELEMENT_HPP_
#define SRC_INCLUDE_ASTELEMENT_HPP_

#include <vector>
#include "AstElementTree.hpp"

class SymbolTable;
class AstElement : public AstElementTree {
 private:
 protected:
  std::vector <AstElementTree *> leaves;
  ElementType type;
 public:
  bool addLeave(AstElementTree *leave);
  void print(int ident = 0);

  void createTestStruct(std::vector <AstTestStruct> *testOutput,
                                int ident = 0);

  bool buildFuncSymbolTable(SymbolTable *s);
  bool compile(SymbolTable *s);


  explicit AstElement(ElementType type) : type(type) {}
};

#endif  // SRC_INCLUDE_ASTELEMENT_HPP_
