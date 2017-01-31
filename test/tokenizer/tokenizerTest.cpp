#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "token.h"
#include "utility.h"

using ::testing::Return;
using namespace std;

TEST(Tokenizer, NoFile) {
  Tokenizer tok;
  vector<Token *> allToken;
  allToken = tok.getAllTokens(NULL);
  EXPECT_EQ( allToken.size(), 0);
}

TEST(Tokenizer, FileOpen) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;

  //myFile.open("testcode.code");

  allToken = tok.getAllTokens(&myFile);

  EXPECT_EQ( allToken.size(), 0);
}

TEST(Tokenizer, Parse) {
  Tokenizer tok;
  vector<Token *> allToken;
  ifstream myFile;
  int i = 0;

  eTokenType expectedType[] = {
    Token_Identifier,
    Token_Operator,
    Token_Double,
    Token_Semilicon,
    Token_Identifier,
    Token_Operator,
    Token_Int,
    Token_Semilicon,
    Token_Brace,
    Token_Brace,
    Token_Brace,
    Token_Brace,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator,
    Token_Operator
   };

  myFile.open("../test/code/testcode.code");

  allToken = tok.getAllTokens(&myFile);

  for (Token *n : allToken) {
    //n->printToken();
    EXPECT_EQ( n->getType(), expectedType[i]);
    i++;
  }

  EXPECT_EQ( allToken.size(), NELEMENTS(expectedType));
}
