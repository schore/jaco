#include "tokenizer.h"

#include "debug_helper.h"

#include "token.h"


using namespace std;

Token * Tokenizer::parse(FILE *pFile) {

  return NULL;
}

vector<Token *> Tokenizer::getAllTokens(FILE *pFile) {
  vector<Token *>  vectorToken;
  Token * t;

  ASSERT(pFile == NULL, vectorToken);

  do {
    t = this->parse(pFile);
    vectorToken.push_back(t);
  } while(t->getType() != Token_Undefined );

  return vectorToken;

}
