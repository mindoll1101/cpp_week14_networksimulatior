#include "router.h"
#include <iostream>

Router::~Router(){
  routingTable_.clear();
}

void Router::receive(){
  bool existDest = false;
  for(int i = 0; i < (int)routingTable_.size(); i++){
    if(packet_ -> destAddress() == routingTable_[i].destination){
      std::cout << "Router #" << id() << ": forwarding packet (from: " << packet_ -> srcAddress().toString() << ", to: " << packet_ -> destAddress().toString() <<", " << packet_ -> dataString().length() << " bytes)" << std::endl;
      routingTable_[i].nextLink -> link(this, packet_);
      existDest = true;
      break;
    }
  }
  if(!existDest){
    std::cout << "Router #" << id() << ": no route for packet (from: " << packet_ -> srcAddress().toString() << ", to: " << packet_ -> destAddress().toString() << ", " << packet_ -> dataString().length() << " bytes)" << std::endl;
  }
}