// copyright 2017 gorg

#include <tokenizer.h>
#include <AstParser.h>

int main() {
  Tokenizer t;
  AstParser p;
  p.parseToken(t.getAllTokens(NULL));
}
