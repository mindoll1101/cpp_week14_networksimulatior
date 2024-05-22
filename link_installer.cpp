#include "link.h"
#include <iostream>

Link *LinkInstaller::install(Node *a, Node *b){
  Link *newLink = new Link(a, b);
  std::cout << "Link: forwarding packet from node #" << newLink -> other(b) -> id() << ", to node #" << newLink -> other(a) -> id() << std::endl;
  return newLink;
}