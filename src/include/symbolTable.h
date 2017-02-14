#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <vector>
#include <set>

class Symbol {
  public:
    std::string str;
    int i;
};


inline bool operator< (const Symbol& lhs, const Symbol& rhs){return lhs.str < rhs.str;   }
inline bool operator==(const Symbol& lhs, const Symbol& rhs){return lhs.str == rhs.str;   }

class SymbolTable
{
private:
  std::vector<std::set<Symbol>> symbolSet;

public:
  SymbolTable();
  virtual ~SymbolTable();

  void pushSymbol(const Symbol sym);
  bool popSymbol(Symbol sym);
  const Symbol *findSymbol(Symbol sym);

  bool checkScope(Symbol sym);

  bool enterScope();
  bool exitScope();
};

#endif /* SYMBOLTABLE_H */
