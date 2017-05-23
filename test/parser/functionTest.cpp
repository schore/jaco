#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "tokenizer.h"
#include "AstParser.h"
#include "AstElementTree.h"
#include "AstElement.h"
#include "AstTerm.h"
#include "utility.h"
#include "symbolTable.h"

using ::testing::Return;
using namespace std;



TEST(Parser, Testfunction) {
  Tokenizer tok;
  AstParser pars;
  int treeDepth = 0;
  vector<Token *> allToken;
  ifstream myFile;

  AstTestStruct aRes[] = {
    {0, AstRoot             , true },
    {1, AstFunc             , true },
    {2, Token_KeywordFunc   , false},
    {2, Token_Identifier    , false},
    {2, Token_BraceLeft     , false},
    {2, Token_BraceRight    , false},
    {2, AstStmt             , true },
    {3, Token_SwiftLeft     , false},
    {3, AstStmtList         , true },
    {4, AstStmt             , true },
    {5, AstStmtAssignment   , true },
    {6, Token_Identifier    , false},
    {6, Token_OperatorAssign, false},
    {6, AstExpr             , true },
    {6, Token_Semilicon     , false},
    {4, AstStmt             , true },
    {5, AstStmtDeclaration  , true },
    {6, Token_KeywordVar    , false},
    {6, Token_Identifier    , false},
    {6, Token_OperatorAssign, false},
    {6, AstExpr             , true },
    {6, Token_Semilicon     , false},
  };

  myFile.open("../test/code/testFunction.code");

  allToken = tok.getAllTokens(&myFile);
  bool succes = pars.parseToken(allToken);

  EXPECT_TRUE(succes);

  AstElementTree *t = pars.getRootNode();
  t->print();

  vector <AstTestStruct> vec;

  t->createTestStruct(&vec);
  int j = 0;

  for (int i = 0; i < vec.size() && j < NELEMENTS(aRes); i++) {
    if (vec[i].nodes > aRes[j].nodes) {
      continue;
    }
    EXPECT_EQ(vec[i].isNode, aRes[j].isNode);
    EXPECT_EQ(vec[i].nodes, aRes[j].nodes);
    EXPECT_EQ(vec[i].type, aRes[j].type);
    j++;
  }
  EXPECT_EQ(j, NELEMENTS(aRes));
}

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
  t->buildEleFuncSymbolTable(s);
}
