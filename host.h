#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <iostream>
#include <vector>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;
  virtual std::string name(){return "Host";}
public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}
  ~Host(){
    for(int i = 0; i < (int)services_.size(); i++){
      delete services_[i];
    }
  }
  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize(){
    for(int i = 0; i < (int)services_.size(); i++){
      services_[i] -> init();
    }
  }

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet){
    std::string message = "sending packet: ";
    message += packet -> toString();
    log(message);
    int n = rand() % links_.size();
    links_[n] -> link(this, packet);
  }

  void receive(Packet *packet){
    // Host #0: received packet, destination port: 3000
    std::string message = "received packet: ";
    message += packet -> toString();
    bool existService = false;
    for(int i = 0; i < (int)services_.size(); i++){
      if(services_[i] -> getPort() == packet -> destPort()){
        message += ", forwarding to " + services_[i] -> toString();
        log(message);
        services_[i] -> execute(packet);
        existService = true;
        break;
      }
    }
    if(!existService){
      std::cout << packet -> destPort() << std::endl;
      std::cout << packet -> destAddress().toString() << std::endl;
      message = "no service for packet: ";
      message += packet -> toString();
      log(message);
      delete packet;
      // Host #0: no service for packet (from: 456, to: 123, 7 bytes)
    }
  }

  std::vector<Service *> getServices(){return services_;}
};

#endif