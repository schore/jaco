#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "token.hpp"
#include "tokenizer.hpp"
#include "utility.hpp"

using ::testing::Return;
using namespace std;

TEST(Tokenizer, NoFile) {
  Tokenizer tok;
  vector<Token *> allToken;
  allToken = tok.getAllTokens(NULL);
  EXPECT_EQ(allToken.size(), 0);
}

TEST(Tokenizer, FileOpen) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;

  // myFile.open("testcode.code");

  allToken = tok.getAllTokens(&myFile);

  EXPECT_EQ(allToken.size(), 0);
}

TEST(Tokenizer, Parse) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  eTokenType expectedType[] = {Token_Identifier,
                               Token_OperatorAssign,
                               Token_Double,
                               Token_Semilicon,
                               Token_Identifier,
                               Token_OperatorAssign,
                               Token_Int,
                               Token_Semilicon,
                               Token_BraceLeft,
                               Token_BraceRight,
                               Token_SwiftLeft,
                               Token_SwiftRight,
                               Token_OperatorPlus,
                               Token_OperatorMinus,
                               Token_OperatorMultiply,
                               Token_OperatorDivide,
                               Token_OperatorShiftLeft,
                               Token_OperatorShiftRight,
                               Token_OperatorSmaller,
                               Token_OperatorGreater,
                               Token_OperatorAnd,
                               Token_OperatorLogicAnd,
                               Token_OperatorOr,
                               Token_OperatorLogicOr,
                               Token_OperatorSmallerEq,
                               Token_OperatorGreaterEq,
                               Token_OperatorNEq,
                               Token_Eof};

  myFile.open("../test/code/testcode.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    // n->printToken();
    EXPECT_EQ(n->getType(), expectedType[i]);
    i++;
  }

  EXPECT_EQ(allToken.size(), NELEMENTS(expectedType));
}
