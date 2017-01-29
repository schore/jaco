#include "tokens/TokenIdentifier.h"

#include "debug_helper.h"
#include <vector>

using namespace std;

TokenIdentifier::TokenIdentifier(vector<char> vect)
  : Token(Token_Identifier)
{
  int count = vect.size();

  this->id = new char[count];

  for (int i = 0; i < count; ++i) {
    this->id[i] = vect[i];
  }
}


TokenIdentifier::~TokenIdentifier() {
  ASSERT(this->id == NULL, )
  delete this->id;
}
