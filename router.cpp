#include "router.h"
#include <iostream>

Router::~Router(){
  routingTable_.clear();
}

void Router::receive(){
  std::cout << "Router #" << id() << ": forwarding packet (from: " << packet_ -> srcAddress().toString() << ", to: " << packet_ -> destAddress().toString() <<", " << packet_ -> dataString().length() << "bytes)" << std::endl;
  for(int i = 0; i < (int)routingTable_.size(); i++){
    if(packet_ -> destAddress() == routingTable_[i].destination){
      routingTable_[i].nextLink -> link(this, packet_);
      break;
    }
  }
}