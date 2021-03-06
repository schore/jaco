#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "token.hpp"
#include "tokenizer.hpp"
#include "utility.hpp"

using ::testing::Return;
using namespace std;

TEST(Token_Int, integer) {

  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  int expectedInt[] = {12, 1, 2, 3,  4,     5,  6,         7,
                       8,  9, 0, 21, 12379, 12, 1234567890};

  myFile.open("../test/code/testint.code");

  allToken = tok.getAllTokens(&myFile);
  allToken.pop_back();

  for (Token *n : allToken) {
    EXPECT_EQ(n->getType(), Token_Int);

    EXPECT_EQ(n->getInt(), expectedInt[i]);
    i++;
  }

  EXPECT_EQ(allToken.size(), NELEMENTS(expectedInt));
}

TEST(Token_Int, special_chars) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  int expectedInt[] = {12, 1, 2, 3,  4,     5,  6,          7,
                       8,  9, 0, 21, 12379, 12, 1234567890, 12};

  myFile.open("../test/code/testintspecialchar.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    if (n->getType() == Token_Int) {
      EXPECT_EQ(n->getInt(), expectedInt[i]);
      i++;
    }
  }

  EXPECT_EQ(i, NELEMENTS(expectedInt));
}
