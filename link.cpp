#include "link.h"
#include "node.h"
#include "router.h"
#include <iostream>

void Link::link(Node *node, Packet *packet){
  Node *o = other(node);
  o -> setPacket(packet);
  std::cout << "Link: forwarding packet from node #" << node -> id() << ", to node #" << other(node) -> id() << std::endl;
  o -> receive();
}