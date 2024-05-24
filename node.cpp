#include "node.h"

int Node::nextId_ = 0;

Node::~Node(){
  for(int i = 0; i < (int)links_.size(); i++){
    delete links_[i];
  }
}

void Node::setPacket(Packet *packet){
  packet_ = packet;
}