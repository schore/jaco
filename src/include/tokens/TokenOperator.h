#ifndef TOKEN_OPERATOR_H_
#define TOKEN_OPERATOR_H_

#include "../token.h"

enum TokenOperatorType {
  TokOperatorUndef,
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

class TokenOperator : public Token {
  const TokenOperatorType opType;

  public:
  TokenOperatorType getOpType() {return this->opType;}

  TokenOperator(TokenOperatorType opType) :
    Token(Token_Operator), opType(opType) {};
};

#endif
