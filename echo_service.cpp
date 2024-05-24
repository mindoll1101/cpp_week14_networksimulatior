#include "echo_service.h"
#include "packet.h"
#include <iostream>

EchoService::~EchoService(){
  delete packet_;
}

void EchoService::send(){
  packet_ = new Packet(host_ -> address(), host_ -> getPacket() -> srcAddress(), port_, host_ -> getPacket() -> srcPort(), host_ -> getPacket() -> data());
  host_ -> send(packet_);
}

void EchoService::init(){
  packet_ = nullptr;
}

void EchoService::execute(){
  std::cout << "EchoService: received \"" << host_ -> getPacket() -> dataString() << "\" from " << host_ -> getPacket() -> srcAddress().toString() << ":" << host_ -> getPacket() -> srcPort() << ", send reply with same data" << std::endl;
  send();
}