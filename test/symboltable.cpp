#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <iostream>

#include "symbolTable.hpp"

using ::testing::Return;
using namespace std;



TEST(SymbolTable, main) {

  SymbolTable dut;
  Symbol a,b,c,d,e,f;

  a.str = "a";
  b.str = "b";
  c.str = "c";
  d.str = "d";
  e.str = "e";
  f.str = "f";

  a.i = 1;
  b.i = 2;
  c.i = 3;
  d.i = 4;
  e.i = 5;
  f.i = 6;

  dut.enterScope();

  dut.pushSymbol(a);
  EXPECT_TRUE(dut.checkScope(a));
  EXPECT_FALSE(dut.checkScope(b));

  dut.pushSymbol(b);
  dut.pushSymbol(c);
  dut.pushSymbol(d);
  dut.pushSymbol(e);

  EXPECT_TRUE(dut.checkScope(a));
  EXPECT_TRUE(dut.checkScope(b));
  EXPECT_TRUE(dut.checkScope(c));
  EXPECT_TRUE(dut.checkScope(d));
  EXPECT_TRUE(dut.checkScope(e));
  EXPECT_FALSE(dut.checkScope(f));

  dut.enterScope();

  EXPECT_FALSE(dut.checkScope(a));
  EXPECT_FALSE(dut.checkScope(b));
  EXPECT_FALSE(dut.checkScope(c));
  EXPECT_FALSE(dut.checkScope(d));
  EXPECT_FALSE(dut.checkScope(e));
  EXPECT_FALSE(dut.checkScope(f));

  dut.pushSymbol(f);

  EXPECT_FALSE(dut.checkScope(a));
  EXPECT_FALSE(dut.checkScope(b));
  EXPECT_FALSE(dut.checkScope(c));
  EXPECT_FALSE(dut.checkScope(d));
  EXPECT_FALSE(dut.checkScope(e));
  EXPECT_TRUE(dut.checkScope(f));

  EXPECT_EQ(dut.findSymbol(a)->i , 1);
  a.i = 10;
  dut.pushSymbol(a);
  EXPECT_EQ(dut.findSymbol(a)->i , 10);
  dut.popSymbol(a);
  EXPECT_EQ(dut.findSymbol(a)->i , 1);


  dut.exitScope();

  EXPECT_TRUE(dut.checkScope(a));
  EXPECT_TRUE(dut.checkScope(b));
  EXPECT_TRUE(dut.checkScope(c));
  EXPECT_TRUE(dut.checkScope(d));
  EXPECT_TRUE(dut.checkScope(e));
  EXPECT_FALSE(dut.checkScope(f));

  EXPECT_EQ(dut.findSymbol(a)->i , 1);
}
