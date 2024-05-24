#include "message_service.h"
#include "packet.h"
#include <iostream>
// 메시지를 전송한다
short MessageService::srcPort_ = 1000;
MessageService::~MessageService(){
  delete packet_;
}
void MessageService::init(){
  port_ = srcPort_++;
  packet_ = nullptr;
}
void MessageService::send(std::string message){
  packet_ = new Packet(host_ -> address(), destAddress_, port_, destPort_, message);
  host_ -> send(packet_);
}

void MessageService::execute(){
  std::cout << "MessageService: received \"" << host_ -> getPacket() -> dataString() << "\" from " << host_ -> getPacket() -> srcAddress().toString() << ":" <<host_ -> getPacket() -> srcPort() << std::endl;
}