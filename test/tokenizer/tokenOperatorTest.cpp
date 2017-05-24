#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.hpp"
#include "token.hpp"
#include "utility.hpp"

using ::testing::Return;
using namespace std;

TEST(TokenOperator, readIn) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  eTokenType expectedType[] = {
    Token_OperatorSmallerEq,
    Token_OperatorPlus,
    Token_OperatorMinus,
    Token_OperatorDivide,
    Token_OperatorMultiply,
    Token_OperatorAssign,
    Token_OperatorEq,
    Token_OperatorNEq,
    Token_OperatorSmallerEq,
    Token_OperatorGreaterEq,
    Token_OperatorGreater,
    Token_OperatorSmaller,
    Token_OperatorLogicAnd,
    Token_OperatorLogicOr,
    Token_OperatorOr,
    Token_OperatorAnd,
    Token_OperatorShiftLeft,
    Token_OperatorShiftRight,
    Token_OperatorModulo,
    Token_Eof,
  };


  myFile.open("../test/code/tokenOperatorTest.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    EXPECT_EQ( n->getType(), expectedType[i]);
    i++;
  }

  EXPECT_EQ( allToken.size(), NELEMENTS(expectedType));
}


TEST(TokenOperator, readInWithChars) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  eTokenType expectedType[] = {
    Token_OperatorSmallerEq,
    Token_OperatorPlus,
    Token_OperatorMinus,
    Token_OperatorDivide,
    Token_OperatorMultiply,
    Token_OperatorAssign,
    Token_OperatorEq,
    Token_OperatorNEq,
    Token_OperatorSmallerEq,
    Token_OperatorGreaterEq,
    Token_OperatorGreater,
    Token_OperatorSmaller,
    Token_OperatorLogicAnd,
    Token_OperatorLogicOr,
    Token_OperatorOr,
    Token_OperatorAnd,
    Token_OperatorShiftLeft,
    Token_OperatorShiftRight,
    Token_OperatorModulo,
  };


  myFile.open("../test/code/tokenOperatorTestChars.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {

    if (n->getType() >= Token_OperatorPlus
        && n->getType() <= Token_OperatorModulo) {
      EXPECT_EQ( n->getType(), expectedType[i]);
      i++;
    }
  }

  EXPECT_EQ( i, NELEMENTS(expectedType));
}
