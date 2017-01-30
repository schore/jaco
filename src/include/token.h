#ifndef TOKEN_H_
#define TOKEN_H_

#define E_TOKEN_TYPE \
  X(Token_Undefined)\
  X(Token_Operator)\
  X(Token_Double)\
  X(Token_Int)\
  X(Token_Keyword)\
  X(Token_Identifier)\
  X(Token_Semilicon)\
  X(Token_Brace)\
  X(Token_Eof)

enum eTokenType {
#define X(_ENUM) _ENUM,
  E_TOKEN_TYPE
#undef X
};

class Token {
    const eTokenType type;

  public:
    Token(eTokenType type) : type(type) {};
    eTokenType getType() {return this->type;};

    void printToken();
};

#endif
