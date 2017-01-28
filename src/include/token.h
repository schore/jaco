#ifndef TOKEN_H_
#define TOKEN_H_

enum eTokenType {
  Token_Undefined,
  Token_Operator,
  Token_Double,
  Token_Int,
  Token_Eof,
};

class Token {
    const eTokenType type;

  protected:
    Token(eTokenType type) : type(type) {};

  public:
    eTokenType getType() {return this->type;};
};

#endif
