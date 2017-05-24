#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.hpp"
#include "AstParser.hpp"
#include "AstElementTree.hpp"
#include "AstElement.hpp"
#include "AstTerm.hpp"
#include "utility.hpp"
#include "symbolTable.hpp"

using ::testing::Return;
using namespace std;


TEST(SymbolTable, Testfunction) {
  Tokenizer tok;
  AstParser pars;
  SymbolTable s;
  int treeDepth = 0;
  vector<Token *> allToken;
  ifstream myFile;


  myFile.open("../test/code/testFunction.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);

  EXPECT_TRUE(succes);

  AstElementTree *t = pars.getRootNode();
  EXPECT_TRUE(s.enterScope());
  EXPECT_TRUE(t->buildFuncSymbolTable(&s));

  EXPECT_TRUE(s.checkScope({"xy1",0}));
  EXPECT_TRUE(s.checkScope({"x3",0}));
  EXPECT_TRUE(s.checkScope({"z2",0}));
  EXPECT_TRUE(s.checkScope({"z3",0}));
}




TEST(SymbolTable, TestfunctionFail) {
  Tokenizer tok;
  AstParser pars;
  SymbolTable s;
  int treeDepth = 0;
  vector<Token *> allToken;
  ifstream myFile;


  myFile.open("../test/code/testFunctionFail.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);

  EXPECT_TRUE(succes);

  AstElementTree *t = pars.getRootNode();
  EXPECT_TRUE(s.enterScope());
  EXPECT_FALSE(t->buildFuncSymbolTable(&s));

  EXPECT_TRUE(s.checkScope({"xy1",0}));
  EXPECT_TRUE(s.checkScope({"x3",0}));
  EXPECT_TRUE(s.checkScope({"z2",0}));
  EXPECT_TRUE(s.checkScope({"z3",0}));
}
