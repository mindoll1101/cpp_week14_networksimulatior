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
bool operator==(NatEntry a, NatEntry b){
  return a.externalPort == b.externalPort && a.internalAddress == b.internalAddress && a.internalPort == b.internalPort;   
}
class Nat : public Node {
private:
  Address address_;
  short externalPort_;
  Link *wanLink_;
  std::vector<NatEntry> natTable_;
  virtual std::string name(){return "Nat";}

  bool checkTable(NatEntry entry){
    for(size_t i = 0; i < natTable_.size(); i++){
      if(entry == natTable_[i]){
        return true;
      }
    }
    return false;
  }

  NatEntry getEntry(Packet *packet){
    NatEntry entry = {0};
    for(size_t i = 0; i < natTable_.size(); i++){
      if(packet -> destPort() == natTable_[i].externalPort){
        entry = natTable_[i];
      }
    }
    return entry;
  }
  
public:
  Nat(Address address) : address_(address) {}
  void setWanLink(Link *link) { wanLink_ = link; }

  virtual void initialize(){
    externalPort_ = 1000;
  }

  virtual void receive(Packet *packet, Link *link){
    if(link == wanLink_){
      NatEntry entry = getEntry(packet);
      Packet *newPacket = new Packet(packet -> srcAddress(), entry.internalAddress, packet -> srcPort(), entry.internalPort, packet -> data());
      for(size_t i = 0; i < links_.size(); i++){
        if(links_[i] != wanLink_){
          links_[i] -> link(this, newPacket);
        }
      }
    }
    else{
      NatEntry entry = {packet -> srcAddress(), packet -> srcPort(), externalPort_++};
      if(checkTable(entry)){
        Packet *newPacket = new Packet(address_, packet -> destAddress(), entry.externalPort, packet -> destPort(), packet -> data());
        wanLink_ -> link(this, newPacket);
      }
      else{
        natTable_.push_back(entry);
        Packet *newPacket = new Packet(address_, packet -> destAddress(), entry.externalPort, packet -> destPort(), packet -> data());
        wanLink_ -> link(this, newPacket);
      }
    }
  }

  Address address(){
    return address_;
  }
};
