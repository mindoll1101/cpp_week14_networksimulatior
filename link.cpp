#include "link.h"
#include "node.h"
#include "router.h"
#include "simulator.h"
#include <iostream>
#include <functional>

void Link::link(Node *node, Packet *packet){
  otherNode_ = other(node);
  packets_.push_back(packet);
  // o -> setPacket(packet);
  std::string message = "packet in: ";
  message += packet -> toString() + " from " + other(otherNode_) -> toString();
  log(message);
  std::function<void()> fptr = [this](){this -> packetOut();};
  Simulator::schedule(Simulator::now() + delay_, fptr);
}

void Link::packetOut(){
  std::string message = "packet out: ";
  message += packets_[sendCount_] -> toString() + " to " + otherNode_ -> toString();
  log(message);
  otherNode_ -> receive(packets_[sendCount_]);
  sendCount_++;
}
