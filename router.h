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
  void receive(Packet *packet, Link *link){
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
      std::string message = "no route for packet: ";
      message += packet -> toString();
      log(message);
    }
  }
};

#endif