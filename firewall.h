#include "address.h"
#include "node.h"
#include "object.h"
#include <set>
#include <string>

class FirewallPolicy : public Object {
friend class Firewall;
private:
  std::string name(){return "FirewallPolicy";}
  std::set<FirewallPolicy *> whiteList_;
public:
  virtual short getPolicyPort(){return -1;};
  virtual Address getPolicyAddr(){return -1;};
  void addWhiteList(FirewallPolicy *policy){whiteList_.insert(policy);}
};

class Firewall : public Node {
private:
  class AllowAnyPolicy : public FirewallPolicy {
  private:
    short destPort_;
    
  public:
    AllowAnyPolicy(short destPort) : destPort_(destPort) {}
    short getPolicyPort(){return destPort_;}
    Address getPolicyAddr(){return Address("*");}
  };

  class AllowSpecificPolicy : public FirewallPolicy {
  private:
    Address srcAddress_;
    short destPort_;

  public:
    AllowSpecificPolicy(Address srcAddress, short destPort)
        : srcAddress_(srcAddress), destPort_(destPort) {}
    short getPolicyPort(){return destPort_;}
    Address getPolicyAddr(){return srcAddress_;}
  };

  Link *receiveLink_ = nullptr;
  Link *otherLink_ = nullptr;
  FirewallPolicy *policy_;

  std::string name(){return "Firewall";}
public:
  Firewall(){
    policy_ = new FirewallPolicy();
  }
  void initialize(){
    for(size_t i = 0; i < links_.size(); i++){
      if(links_[i] != receiveLink_){
        otherLink_ = links_[i];
        break;
      }
    }
  }

  void setReceiveLink(Link *link) { receiveLink_ = link; }

  void receive(Packet *packet, Link *link){
    if(link == receiveLink_){
      for(FirewallPolicy *policy : policy_ -> whiteList_){
        if(policy -> getPolicyPort() == packet -> destPort()){
          if(policy -> getPolicyAddr().toString() == "*" || policy -> getPolicyAddr().toString() == packet -> srcAddress().toString()){
            otherLink_ -> link(this, packet);
            return;
          }
        }
      }
      std::string message = "Dropping ";
      message += packet -> toString() + " with src address " + packet -> srcAddress().toString() + " and dest port " + std::to_string(packet -> destPort());
      log(message);
    }
    else{
      receiveLink_ -> link(this, packet);
    }
  }

  void addAllowAnyPolicy(short destPort){
    FirewallPolicy *anyPolicy = new AllowAnyPolicy(destPort);
    policy_ -> addWhiteList(anyPolicy);
  }

  void addAllowSpecificPolicy(Address srcAddress, short destPort){
    FirewallPolicy *specificPolicy = new AllowSpecificPolicy(srcAddress, destPort);
    policy_ -> addWhiteList(specificPolicy);
  }
};