#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "tokens/TokenKeyword.h"
#include "utility.h"

using ::testing::Return;
using namespace std;


TEST(Keyword, Parse) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  TokenKeywordType expectedType[] = {
    TokenKeywordIf,
    TokenKeywordElse,
    TokenKeywordWhile,
    TokenKeywordFor,
    TokenKeywordIf,
    TokenKeywordElse,
    TokenKeywordWhile,
    TokenKeywordFor,
   };

  myFile.open("../test/code/keywordtest.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {

    if (n->getType() == Token_Keyword) {
      TokenKeyword *ti = (TokenKeyword *) n;
      EXPECT_EQ( ti->getKeywordType(), expectedType[i]);
      i++;
    }
  }

  EXPECT_EQ( i, NELEMENTS(expectedType));
}
