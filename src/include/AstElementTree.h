#ifndef ASTELEMENTTREE_H
#define ASTELEMENTTREE_H

#include <vector>

struct AstTestStruct {
  int nodes;
  int type;
  bool isNode;
};


class AstElementTree
{
private:
protected:
public:
  virtual void print(int ident = 0) = 0;
  virtual void createTestStruct(std::vector <AstTestStruct> &testOutput,
                                int ident = 0) = 0;

  AstElementTree() {};
  virtual ~AstElementTree() {};
};

#endif /* ASTELEMENTTREE_H */
