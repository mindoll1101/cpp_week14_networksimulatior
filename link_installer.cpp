#include "link.h"
#include "link_installer.h"
#include "node.h"

Link *LinkInstaller::install(Node *a, Node *b, double delay){
  Link *newLink = new Link(a, b, delay);
  (a -> Node::links_).push_back(newLink);
  (b -> Node::links_).push_back(newLink);
  return newLink;
}