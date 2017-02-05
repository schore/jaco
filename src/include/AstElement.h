#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "AstElementTree.h"
#include <vector>

class AstElement : public AstElementTree
{
private:
  std::vector <AstElement *> leaves;

public:
  void addLeave(AstElement *leave);
  void removLeaves();

  AstElement() {};
  virtual ~AstElement() {};
};

#endif /* ASTELEMENT_H */
