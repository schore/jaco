#include "tokenizer.h"

#include "debug_helper.h"

#include "token.h"
#include "tokens/TokenOperator.h"
#include "tokens/TokenInt.h"
#include "tokens/TokenDouble.h"
#include "utility.h"


using namespace std;

struct StringToOperator {
  const char* str;
  int size;
  TokenOperatorType tok;
};


template <class T> bool inList(vector<T> vect, T item) {
  T var;
  for (T n : vect) {
    if (var == n) return true;
  }
  return false;
}

static const vector<char> emptySpace = {
  ' ','\n'};

static const vector<char> oper = {
  '+', '-', '*', '/', '|', '&', '%', '!'};

static const vector<char> brace = {
  '(', ')', '{', '}'};

#define MAPPING_TABLE\
  X("+" ,    TokOperatorPlus)\
  X("-" ,    TokOperatorMinus)\
  X("/" ,    TokOperatorDivide)\
  X("*" ,    TokOperatorMultiply)\
  X("=" ,    TokOperatorAssign)\
  X("==",    TokOperatorEq)\
  X("!=",    TokOperatorNEq)\
  X("<=",    TokOperatioSmallerEq)\
  X(">=",    TokOperatorGreaterEq)\
  X(">" ,    TokOperatorGreater)\
  X("<" ,    TokOperatorSmaller)\
  X("&&",    TokOperatorLogicAnd)\
  X("||",    TokOperatorLogicOr)\
  X("|" ,    TokOperatorOr)\
  X("&" ,    TokOperatorAnd)\
  X("<<",    TokOperatorShiftLeft)\
  X(">>",    TokOperatorShiftRight)\
  X("%" ,    TokOperatorModulo)\

static const vector<StringToOperator> MappingOperators = {
#define X(_CHAR, _TOKEN) { _CHAR, sizeof(_CHAR)-1, _TOKEN},
  MAPPING_TABLE
#undef X
};



bool Tokenizer::isAllowedChar(char c) {
  if (isalpha(c)) return true;
  if (c == '_') return true;
  return false;
}

bool Tokenizer::isOperator(char c) {
  return inList<char>(oper, c);
}

bool Tokenizer::isBrace(char c) {
  return inList<char>(brace, c);
}

void Tokenizer::removeSpace(ifstream *pFile) {
  char c;
  bool inList = false;

  ASSERT(pFile == NULL,  );

  do {
    inList = false;
    pFile->get(c);
    for (char n : emptySpace) {
      if (n == c) {
        inList = true;
        break;
      }
    }
  } while (inList);
}


Token *Tokenizer::createOperator(std::ifstream *pFile) {
  char c1,c2;
  Token *t;
  //if not in list there is no endless loop 
  int weight=1;
  TokenOperatorType opType = TokOperatorUndef;


  pFile->get(c1);
  pFile->get(c2);
  for (StringToOperator map: MappingOperators ) {
    if (map.size == 1 && map.str[0] == c1) {
      weight = 1;
      opType = map.tok;
    }
    else if (map.size == 2 &&
        map.str[0] == c1 && map.str[1] == c2) {
      weight = 2;
      opType = map.tok;
    }
  }

  pFile->seekg(weight-2, ios_base::cur);

  return new TokenOperator(opType);
}

Token *Tokenizer::createNumber(std::ifstream *pFile){
  double parsedDouble;
  long long int parsedInt = 0;
  int count = 0;
  char c;
  bool isDouble;

  while(true) {
    pFile->get(c);
    if (isdigit(c)) {
      if (!isDouble) {
        parsedInt = parsedInt*10 + c - '0';
      }
      else {
        count++;
        parsedDouble += (double)(c -'0')/(count*10.0);
      }
    }
    else if ( c == '.' && !isDouble) {
      isDouble = true;
      parsedDouble = parsedInt;
    }
    else if ( c == ' ' || c == ';' || c == '\n' ) {
      if ( c == ';') {
        pFile->seekg(-1, ios_base::cur);
      }
      if (isDouble) return new TokenDouble(parsedDouble);
      else return new TokenInt(parsedInt);
    }
    else {
      ASSERT(true, NULL);
    }
  }
}

Token *Tokenizer::createWord(std::ifstream *pFile){
}

Token *Tokenizer::createBrace(std::ifstream *pFile){
}

Token * Tokenizer::parse(ifstream *pFile) {
  this->removeSpace(pFile);
  char c;
  pFile->get(c);
  pFile->seekg(-1, ios_base::cur);

  if(isdigit(c)) {
    return this->createNumber(pFile);
  }
  else if (this->isAllowedChar(c)) {
    return this->createWord(pFile);
  }
  else if (this->isOperator(c)) {
    return this->createOperator(pFile);
  }
  else if (this->isBrace(c)) {
    return this->createBrace(pFile);
  }

  DEBUG_PRINT("Default Reached Char not allowed??");
  return NULL;
}

vector<Token *> Tokenizer::getAllTokens(ifstream *pFile) {
  vector<Token *>  vectorToken;
  Token * t;

  ASSERT(pFile == NULL, vectorToken);

  do {
    t = this->parse(pFile);
    vectorToken.push_back(t);
  } while(t->getType() != Token_Undefined );

  return vectorToken;

}
