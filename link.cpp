#include "link.h"
#include "node.h"
#include "router.h"
#include "simulator.h"
#include <iostream>
#include <functional>

void Link::link(Node *sender, Packet *packet){
  // o -> setPacket(packet);
  std::string message = "packet in: ";
  message += packet -> toString() + " from " + sender -> toString();
  log(message);
  std::function<void()> fptr = [sender, packet, this]() -> void{
    std::string message = "packet out: ";
    message += packet -> toString() + " to " + other(sender) -> toString();
    log(message);
    other(sender) -> receive(packet, this);
  };
  Simulator::schedule(Simulator::now() + delay_, fptr);
}
