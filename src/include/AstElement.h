#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "AstElementTree.h"
#include <vector>

class AstElement : public AstElementTree
{
private:
  std::vector <AstElement *> leaves;
  int type;

public:
  void addLeave(AstElement *leave);
  void removeLeaves();

  AstElement() {};
  virtual ~AstElement() {};
};

#endif /* ASTELEMENT_H */
