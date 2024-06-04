#include "node.h"

int Node::nextId_ = 0;

void Node::setPacket(Packet *packet){
  packet_ = packet;
}