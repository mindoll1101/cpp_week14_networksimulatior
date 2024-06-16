#include "address.h"
#include "host.h"
#include "link.h"
#include <set>
#include <vector>

struct NatEntry {
  Address internalAddress;
  short internalPort;
  short externalPort;
};

class Nat : public Node {
private:
  Address address_;

  Link *wanLink_;
  std::vector<NatEntry> natTable_;
  virtual std::string name(){return "Nat";}
public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }
  virtual void initialize(){
    short externalPort = 1000;
    for(size_t i = 0; i < links_.size(); i++){
      if(links_[i] -> other(this) -> toString().find("<Host>") != std::string::npos){
        Host *internal = dynamic_cast<Host *>(links_[i] -> other(this));
        for(size_t j = 0; j < internal -> getServices().size(); j++){
          NatEntry entry = {internal -> address(), internal -> getServices()[j] -> getPort(), externalPort++};
          natTable_.push_back(entry);
        }
      }
    }
  }
  virtual void receive(Packet *packet, Link *link){
    for(size_t i = 0; i < natTable_.size(); i++){
      if(link == wanLink_ && natTable_[i].externalPort == packet -> destPort()){
        Packet *newPacket = new Packet(packet -> srcAddress(), natTable_[i].internalAddress, packet -> srcPort(), natTable_[i].internalPort, packet -> data());
        for(size_t j = 0; j < links_.size(); j++){
          if(links_[j] != wanLink_){
            links_[j] -> link(this, newPacket);
          }
        }
      }
      else if(link != wanLink_ && natTable_[i].internalAddress == packet -> srcAddress()){
        Packet *newPacket = new Packet(address_, packet -> destAddress(), natTable_[i].externalPort, packet -> destPort(), packet -> data());
        wanLink_ -> link(this, newPacket);
      }
    }
  }

  Address address(){
    return address_;
  }
};
