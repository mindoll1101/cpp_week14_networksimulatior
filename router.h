#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
};

class Router : public Node {
private:
  virtual std::string name(){return "Router";}
protected:
  // Address srcAddress_;
  std::vector<RoutingEntry> routingTable_;
public:
  ~Router(){
    routingTable_.clear();
  }
  void receive(Packet *packet){
    bool existDest = false;
    for(int i = 0; i < (int)routingTable_.size(); i++){
      if(packet -> destAddress() == routingTable_[i].destination){
        std::string message = "forwarding packet: ";
        message += packet -> toString() + " to " + routingTable_[i].nextLink -> toString();
        log(message);
        routingTable_[i].nextLink -> link(this, packet);
        existDest = true;
        break;
      }
    }
    if(!existDest){
      std::cout << "Router #" << id() << ": no route for packet (from: " << packet -> srcAddress().toString() << ", to: " << packet -> destAddress().toString() << ", " << packet -> dataString().length() << " bytes)" << std::endl;
    }
  }
};

#endif