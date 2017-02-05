#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "AstParser.h"

using ::testing::Return;
using namespace std;

TEST(Parser, Testfunction) {
  Tokenizer tok;
  AstParser pars;
  vector<Token *> allToken;
  ifstream myFile;

  myFile.open("../test/code/testFunction.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);
}
