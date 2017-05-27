// copyright 2017 gorg

#include <AstParser.hpp>
#include <tokenizer.hpp>

int main() {
  Tokenizer t;
  AstParser p;
  p.parseToken(t.getAllTokens(nullptr));
}
