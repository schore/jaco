// copyright 2017 gorg

#include <tokenizer.hpp>
#include <AstParser.hpp>

int main() {
  Tokenizer t;
  AstParser p;
  p.parseToken(t.getAllTokens(NULL));
}
