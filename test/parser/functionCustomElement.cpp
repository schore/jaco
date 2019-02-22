#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>

#include "AstElement.hpp"
#include "AstElementTree.hpp"
#include "AstParser.hpp"
#include "AstTerm.hpp"
#include "symbolTable.hpp"
#include "tokenizer.hpp"
#include "utility.hpp"

using ::testing::Return;
using namespace std;

TEST(SymbolTable, Testfunction) {
  Tokenizer tok;
  AstParser pars;
  SymbolTable s;
  vector<Token *> allToken;
  ifstream myFile;

  myFile.open("../test/code/testFunction.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);

  EXPECT_TRUE(succes);

  AstElementTree *t = pars.getRootNode();
  EXPECT_TRUE(s.enterScope());
  EXPECT_TRUE(t->buildFuncSymbolTable(&s));

  EXPECT_TRUE(s.checkScope({"xy1", 0}));
  EXPECT_TRUE(s.checkScope({"x3", 0}));
  EXPECT_TRUE(s.checkScope({"z2", 0}));
  EXPECT_TRUE(s.checkScope({"z3", 0}));
}

TEST(SymbolTable, TestfunctionFail) {
  Tokenizer tok;
  AstParser pars;
  SymbolTable s;
  vector<Token *> allToken;
  ifstream myFile;

  myFile.open("../test/code/testFunctionFail.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);

  EXPECT_TRUE(succes);

  AstElementTree *t = pars.getRootNode();
  EXPECT_TRUE(s.enterScope());
  EXPECT_FALSE(t->buildFuncSymbolTable(&s));

  EXPECT_TRUE(s.checkScope({"xy1", 0}));
  EXPECT_TRUE(s.checkScope({"x3", 0}));
  EXPECT_TRUE(s.checkScope({"z2", 0}));
  EXPECT_TRUE(s.checkScope({"z3", 0}));
}
