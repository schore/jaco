#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "token.h"
#include "tokens/TokenOperator.h"
#include "utility.h"

using ::testing::Return;
using namespace std;

TEST(TokenOperator, readIn) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  TokenOperatorType expectedType[] = {
    TokOperatioSmallerEq,
    TokOperatorPlus,
    TokOperatorMinus,
    TokOperatorDivide,
    TokOperatorMultiply,
    TokOperatorAssign,
    TokOperatorEq,
    TokOperatorNEq,
    TokOperatioSmallerEq,
    TokOperatorGreaterEq,
    TokOperatorGreater,
    TokOperatorSmaller,
    TokOperatorLogicAnd,
    TokOperatorLogicOr,
    TokOperatorOr,
    TokOperatorAnd,
    TokOperatorShiftLeft,
    TokOperatorShiftRight,
    TokOperatorModulo,
  };


  myFile.open("../test/code/tokenOperatorTest.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    EXPECT_EQ( n->getType(), Token_Operator);

    TokenOperator *ti = (TokenOperator *) n;
    EXPECT_EQ( ti->getOpType(), expectedType[i]);
    i++;
  }

  EXPECT_EQ( allToken.size(), NELEMENTS(expectedType));
}


TEST(TokenOperator, readInWithChars) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  TokenOperatorType expectedType[] = {
    TokOperatioSmallerEq,
    TokOperatorPlus,
    TokOperatorMinus,
    TokOperatorDivide,
    TokOperatorMultiply,
    TokOperatorAssign,
    TokOperatorEq,
    TokOperatorNEq,
    TokOperatioSmallerEq,
    TokOperatorGreaterEq,
    TokOperatorGreater,
    TokOperatorSmaller,
    TokOperatorLogicAnd,
    TokOperatorLogicOr,
    TokOperatorOr,
    TokOperatorAnd,
    TokOperatorShiftLeft,
    TokOperatorShiftRight,
    TokOperatorModulo,
  };


  myFile.open("../test/code/tokenOperatorTestChars.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {

    if (n->getType() == Token_Operator) {
      TokenOperator *ti = (TokenOperator *) n;
      EXPECT_EQ( ti->getOpType(), expectedType[i]);
      i++;
    }
  }

  EXPECT_EQ( i, NELEMENTS(expectedType));
}
