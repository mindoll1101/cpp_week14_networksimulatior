#include "link.h"
#include "node.h"
#include "router.h"
#include "simulator.h"
#include <iostream>
#include <functional>

void Link::link(Node *node, Packet *packet){
  packets_.push_back(std::make_pair(other(node), packet));
  // o -> setPacket(packet);
  std::string message = "packet in: ";
  message += packet -> toString() + " from " + node -> toString();
  log(message);
  std::function<void()> fptr = [this](){this -> packetOut();};
  Simulator::schedule(Simulator::now() + delay_, fptr);
}

void Link::packetOut(){
  std::string message = "packet out: ";
  message += packets_[sendCount_].second -> toString() + " to " + packets_[sendCount_].first -> toString();
  log(message);
  packets_[sendCount_].first -> receive(packets_[sendCount_].second, this);
  sendCount_++;
}
