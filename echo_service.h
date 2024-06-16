#ifndef ECHO_SERVICE_H
#define ECHO_SERVICE_H

#include "host.h"
#include "service.h"
#include "packet.h"
#include <iostream>
#include <string>

// 수신한 패킷을 전송자에게 다시 전송하는 서비스
class EchoService : public Service {
  friend class EchoServiceInstaller;

private:
  virtual std::string name(){return "EchoService";}
  Packet *packet_;
  EchoService(Host *host, short port) : Service(host, port) {}
  
public:
  void initialize(){
    packet_ = nullptr;
  }
  void send(Packet *packet){
    packet_ = new Packet(host_ -> address(), packet -> srcAddress(), port_, packet -> srcPort(), packet -> data());
    host_ -> send(packet_);
  }
  void execute(Packet *packet){
    std::string message = "received \"" + packet -> dataString() + "\" from " + packet -> srcAddress().toString() + ":" 
                        + std::to_string(packet -> srcPort()) + " send reply with same data";
    log(message);
    send(packet);
  }
};

#endif