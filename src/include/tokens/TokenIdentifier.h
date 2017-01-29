#ifndef TOKENIDENTIFIER_H
#define TOKENIDENTIFIER_H

#include "../token.h"

#include <vector>

class TokenIdentifier : public Token
{
private:
  char *id;
public:
  TokenIdentifier(std::vector<char> vect);
  virtual ~TokenIdentifier();
};

#endif /* TOKENIDENTIFIER_H */
