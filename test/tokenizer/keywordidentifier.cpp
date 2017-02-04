#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "token.h"
#include "utility.h"

using ::testing::Return;
using namespace std;


TEST(Keyword, Parse) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  eTokenType expectedType[] = {
    Token_KeywordIf,
    Token_KeywordElse,
    Token_KeywordWhile,
    Token_KeywordFor,
    Token_KeywordIf,
    Token_KeywordElse,
    Token_KeywordWhile,
    Token_KeywordFor,
   };

  myFile.open("../test/code/keywordtest.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {

    if (n->getType() >= Token_KeywordIf
        && n->getType() <= Token_KeywordElse) {
      EXPECT_EQ( n->getType(), expectedType[i]);
      i++;
    }
  }

  EXPECT_EQ( i, NELEMENTS(expectedType));
}
