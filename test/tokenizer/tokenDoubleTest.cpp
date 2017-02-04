#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "token.h"
#include "utility.h"

using ::testing::Return;
using namespace std;

TEST(TokenDouble, readIn) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  double expectedDouble[] =
  {676544.58432, 9.12345, 1.1, 3.5, 0.12345, 676544.584329};

  myFile.open("../test/code/testdouble.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    EXPECT_EQ( n->getType(), Token_Double);

    EXPECT_DOUBLE_EQ( n->getDouble(), expectedDouble[i]);
    i++;
  }

  EXPECT_EQ( allToken.size(), NELEMENTS(expectedDouble));
}

TEST(TokenDouble, SpecialChars) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  double expectedDouble[] =
  {676544.58432, 9.12345, 1.1, 3.5, 0.12345, 676544.584329, 5.1};

  myFile.open("../test/code/testdoublewithchar.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    if (n->getType() == Token_Double) {
      EXPECT_DOUBLE_EQ( n->getDouble(), expectedDouble[i]);
      i++;
    }
  }

  EXPECT_EQ( i, NELEMENTS(expectedDouble));

}
