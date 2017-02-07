#include "AstElement.h"

using namespace std;

void AstElement::addLeave(AstElement *leave) {
  this->leaves.push_back(leave);
}
