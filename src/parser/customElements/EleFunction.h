#ifndef ELEFUNCTION_H
#define ELEFUNCTION_H

#include "AstElement.h"

class EleFunction : public AstElement
{
private:
 

public:
  EleFunction() : AstElement(AstFunc) {};
  virtual ~EleFunction() {};
};

#endif /* ELEFUNCTION_H */
