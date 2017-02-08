#ifndef ASTELEMENTTREE_H
#define ASTELEMENTTREE_H

class AstElementTree
{
private:

public:
  virtual void print(int ident = 0) = 0;

  AstElementTree() {};
  virtual ~AstElementTree() {};
};

#endif /* ASTELEMENTTREE_H */
