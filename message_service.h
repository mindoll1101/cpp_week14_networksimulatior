#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "address.h"
#include "host.h"
#include "service.h"
#include "packet.h"
#include <iostream>

#define CLIENT_PORT 1000

// send 함수를 호출하여 메시지를 전송할 수 있는 서비스
class MessageService : public Service {
  friend class MessageServiceInstaller;

private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;
  Packet *packet_;
  virtual std::string name(){return "MessageService";}
  MessageService(Host *host, short port, Address destAddress, short destPort)
      : Service(host, port), destAddress_(destAddress), destPort_(destPort) {}

public:
  // 메시지를 전송한다
  void init(){
    packet_ = nullptr;
  }
  void send(std::string message){
    packet_ = new Packet(host_ -> address(), destAddress_, port_, destPort_, message);
    host_ -> send(packet_);
  }
  void execute(Packet *packet){
    std::string message = packet -> dataString();
    log(message);
    delete packet;
  }
};

#endif