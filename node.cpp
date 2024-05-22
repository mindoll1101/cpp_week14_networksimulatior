#include "node.h"

bool Node::operator==(Node *a){
  if(a -> id() == id_){
    return true;
  }
  else
    return false;
}