#include "tokenizer.h"

#include "debug_helper.h"

#include "token.h"
#include "utility.h"


using namespace std;

struct StringToOperator {
  const char* str;
  int size;
  eTokenType tok;
};

struct StringToKeyword {
  const char* str;
  int size;
  eTokenType type;
};


template <class T> bool inList(vector<T> vect, T item) {
  for (T n : vect) {
    if (item == n) return true;
  }
  return false;
}

static const vector<char> emptySpace = {
  ' ', '\n'};

static const vector<char> oper = {
  '+', '-', '*', '/', '|', '&', '%', '!', '=', '<', '>'};

static const vector<char> brace = {
  '(', ')', '{', '}'};

#define MAPPING_TABLE\
  X("+" ,    Token_OperatorPlus)\
  X("-" ,    Token_OperatorMinus)\
  X("/" ,    Token_OperatorDivide)\
  X("*" ,    Token_OperatorMultiply)\
  X("=" ,    Token_OperatorAssign)\
  X("==",    Token_OperatorEq)\
  X("!=",    Token_OperatorNEq)\
  X("<=",    Token_OperatorSmallerEq)\
  X(">=",    Token_OperatorGreaterEq)\
  X(">" ,    Token_OperatorGreater)\
  X("<" ,    Token_OperatorSmaller)\
  X("&&",    Token_OperatorLogicAnd)\
  X("||",    Token_OperatorLogicOr)\
  X("|" ,    Token_OperatorOr)\
  X("&" ,    Token_OperatorAnd)\
  X("<<",    Token_OperatorShiftLeft)\
  X(">>",    Token_OperatorShiftRight)\
  X("%" ,    Token_OperatorModulo)\
  X("!" ,    Token_OperatorNot)

static const vector<StringToOperator> MappingOperators = {
#define X(_CHAR, _TOKEN) { _CHAR, sizeof(_CHAR)-1, _TOKEN},
  MAPPING_TABLE
#undef X
};

#define KEYWORD_TABLE\
  X("if"    , Token_KeywordIf    )\
  X("while" , Token_KeywordWhile )\
  X("for"   , Token_KeywordFor   )\
  X("else"  , Token_KeywordElse  )\
  X("func"  , Token_KeywordFunc  )\
  X("var"   , Token_KeywordVar   )

static const vector<StringToKeyword> MappingKeywords = {
#define X(_STR, _TYPE) {_STR, sizeof(_STR)-1, _TYPE},
  KEYWORD_TABLE
#undef X
};

static const vector<char> specialChars = {
  ';' , ','
};

bool Tokenizer::isAllowedChar(char c) {
  if (isalpha(c)) return true;
  if (isdigit(c)) return true;
  if (c == '_') return true;
  return false;
}

bool Tokenizer::isOperator(char c) {
  return inList<char>(oper, c);
}

bool Tokenizer::isBrace(char c) {
  return inList<char>(brace, c);
}

bool Tokenizer::isSpecialChar(char c) {
  return inList<char>(specialChars, c);
}

bool Tokenizer::isEmptySpace(char c) {
  return inList<char>(emptySpace, c);
}

bool Tokenizer::isEndOfSequence(char c) {
  if (this->isOperator(c)) return true;
  if (this->isBrace(c)) return true;
  if (this->isSpecialChar(c)) return true;
  if (this->isEmptySpace(c)) return true;
  return false;
}

void Tokenizer::removeSpace(ifstream *pFile) {
  char c;
  while (inList<char>(emptySpace, pFile->peek()))
    pFile->get(c);
}


Token *Tokenizer::createOperator(std::ifstream *pFile) {
  char c1,c2;
  Token *t;
  //if not in list there is no endless loop 
  int weight=1;
  eTokenType opType = Token_Undefined;

  pFile->get(c1);
  c2 = pFile->peek();
  for (StringToOperator map: MappingOperators ) {
    if (map.size == 1 && map.str[0] == c1) {
      weight = 1;
      opType = map.tok;
    }
    else if (map.size == 2 &&
        map.str[0] == c1 && map.str[1] == c2) {
      weight = 2;
      opType = map.tok;
      pFile->get(c2);
      break;
    }
  }

  return new Token(opType);
}

Token *Tokenizer::createNumber(std::ifstream *pFile){
  double parsedDouble=0;
  long long int parsedInt = 0;
  double count = 10.0;
  char c;
  bool isDouble=false;

  while(true) {
    pFile->get(c);
    if (isdigit(c)) {
      if (!isDouble) {
        parsedInt = parsedInt*10 + c - '0';
      }
      else {
        parsedDouble += (((double)(c -'0'))/(count));
        count *= 10;
      }
    }
    else if ( c == '.' && !isDouble) {
      isDouble = true;
      parsedDouble = parsedInt;
    }
    else if (this->isEndOfSequence(c)) {
      pFile->seekg(-1, ios_base::cur);
      if (isDouble) {
        Token *t = new Token(Token_Double);
        t->setDouble(parsedDouble);
        return t;
      }
      else {
        Token *t = new Token(Token_Int);
        t->setInt(parsedInt);
        return t;
      }
    }
    else {
      ASSERT(true, NULL);
    }
  }
}

Token *Tokenizer::createKeyword(ifstream *pFile) {
  char c;

  for(StringToKeyword map : MappingKeywords) {
    int i;
    bool match = true;

    for (i=0; i < map.size; i++) {
      pFile->get(c);
      c = tolower(c);
      if ( map.str[i] != c ) {
        match = false;
        break;
      }
    }

    if (match) {
      pFile->get(c);
      i++;
      if (this->isEndOfSequence(c)) {
        return new Token(map.type);
      }
    }
    pFile->seekg(-i -1, ios_base::cur);
  }

  return NULL;
}

Token *Tokenizer::createIdentifier(ifstream *pFile) {
  char c;

  vector<char> idStr;

  pFile->get(c);
  while(this->isAllowedChar(c)) {
    idStr.push_back(c);
    pFile->get(c);
  }
  pFile->seekg(-1, ios::cur);

  Token *t = new Token(Token_Identifier);
  t->setStr(idStr);
  return t;

}

Token *Tokenizer::createWord(std::ifstream *pFile){
  //defaut Case generate Keyword
  Token *t = this->createKeyword(pFile);
  if (t != NULL) {
    return t;
  }
  else {
    return this->createIdentifier(pFile);
  }
}

Token *Tokenizer::createSpecialChar(std::ifstream *pFile) {
  char c;
  pFile->get(c);
  switch (c) {
    case ';': return new Token(Token_Semilicon);
    case ',': return new Token(Token_Comma);
    default:  return new Token(Token_Error);
  }
}

Token *Tokenizer::createBrace(std::ifstream *pFile){
  char c;
  pFile->get(c);
  switch(c) {
    case '(': return new Token(Token_BraceLeft);
    case ')': return new Token(Token_BraceRight);
    case '{': return new Token(Token_SwiftLeft);
    case '}': return new Token(Token_SwiftRight);
    default:
      break;
  }
  ASSERT(true, NULL);
}

Token * Tokenizer::parse(ifstream *pFile) {
  this->removeSpace(pFile);
  char c;
  //pFile->get(c);
  //pFile->seekg(-1, ios_base::cur);
  c = pFile->peek();

  if(isdigit(c))                   return this->createNumber(pFile);
  else if (this->isAllowedChar(c)) return this->createWord(pFile);
  else if (this->isOperator(c))    return this->createOperator(pFile);
  else if (this->isBrace(c))       return this->createBrace(pFile);
  else if (this->isSpecialChar(c)) return this->createSpecialChar(pFile);

  return NULL;
}

vector<Token *> Tokenizer::getAllTokens(ifstream *pFile) {
  vector<Token *>  vectorToken;
  Token * t;
  int filePos = -1;

  ASSERT(pFile == NULL, vectorToken);
  ASSERT(!pFile->is_open() , vectorToken);

  while(!pFile->eof()) {
    filePos = pFile->tellg();
    t = this->parse(pFile);
    if (t != NULL) {
      vectorToken.push_back(t);
    }
  }
  vectorToken.push_back(new Token(Token_Eof));
  return vectorToken;

}
