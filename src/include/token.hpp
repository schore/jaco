// copyright 2017 gorg
#ifndef SRC_INCLUDE_TOKEN_HPP_
#define SRC_INCLUDE_TOKEN_HPP_

#include <string>
#include <vector>

#define E_TOKEN_TYPE                                                           \
  X(Token_Undefined)                                                           \
  X(Token_OperatorPlus)                                                        \
  X(Token_OperatorMinus)                                                       \
  X(Token_OperatorDivide)                                                      \
  X(Token_OperatorMultiply)                                                    \
  X(Token_OperatorAssign)                                                      \
  X(Token_OperatorEq)                                                          \
  X(Token_OperatorNEq)                                                         \
  X(Token_OperatorSmallerEq)                                                   \
  X(Token_OperatorGreaterEq)                                                   \
  X(Token_OperatorGreater)                                                     \
  X(Token_OperatorSmaller)                                                     \
  X(Token_OperatorLogicAnd)                                                    \
  X(Token_OperatorLogicOr)                                                     \
  X(Token_OperatorOr)                                                          \
  X(Token_OperatorAnd)                                                         \
  X(Token_OperatorShiftLeft)                                                   \
  X(Token_OperatorShiftRight)                                                  \
  X(Token_OperatorNot)                                                         \
  X(Token_OperatorModulo)                                                      \
  X(Token_Double)                                                              \
  X(Token_Int)                                                                 \
  X(Token_Keyword)                                                             \
  X(Token_Identifier)                                                          \
  X(Token_Semilicon)                                                           \
  X(Token_Comma)                                                               \
  X(Token_BraceLeft)                                                           \
  X(Token_BraceRight)                                                          \
  X(Token_SwiftLeft)                                                           \
  X(Token_SwiftRight)                                                          \
  X(Token_KeywordIf)                                                           \
  X(Token_KeywordVar)                                                          \
  X(Token_KeywordWhile)                                                        \
  X(Token_KeywordFor)                                                          \
  X(Token_KeywordElse)                                                         \
  X(Token_KeywordFunc)                                                         \
  X(Token_Eof)                                                                 \
  X(Token_Error)

enum eTokenType {
#define X(_ENUM) _ENUM,
  E_TOKEN_TYPE
#undef X
};

class Token {
  const eTokenType type;

  double dValue;
  int intValue;

  std::string str;

public:
  explicit Token(eTokenType type);

  eTokenType getType() { return this->type; }

  void printToken();

  void setInt(int intValue) { this->intValue = intValue; }
  int getInt() { return this->intValue; }

  void setDouble(double dValue) { this->dValue = dValue; }
  double getDouble() { return this->dValue; }

  void setStr(std::string str);
  std::string getString() const { return this->str; }
};

#endif // SRC_INCLUDE_TOKEN_HPP_
