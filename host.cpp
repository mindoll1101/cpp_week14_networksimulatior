#include "host.h"
#include "address.h"
#include <cstdlib>
#include <iostream>

// 호스트와 설치된 서비스를 전부 초기화한다.
Host::~Host(){
  for(int i = 0; i < (int)services_.size(); i++){
    delete services_[i];
  }
}
void Host::initialize(){
  for(int i = 0; i < (int)services_.size(); i++){
    services_[i] -> init();
  }
}

void Host::receive(){
  // Host #0: received packet, destination port: 3000
  std::cout << "Host #" << id() << ": received packet, destination port: " << packet_ -> destPort() << std::endl;
  bool existService = false;
  for(int i = 0; i < (int)services_.size(); i++){
    if(services_[i] -> getPort() == packet_ -> destPort()){
      services_[i] -> execute();
      existService = true;
      break;
    }
  }
  if(!existService){
    std::cout << "Host #" << id() << ": no service for packet (from: " << packet_ -> srcAddress().toString() << ", to: " << packet_ -> destAddress().toString() << ", " << packet_ -> dataString().length() << " bytes)" << std::endl;
    // Host #0: no service for packet (from: 456, to: 123, 7 bytes)
  }
}

// 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
void Host::send(Packet *packet){
  std::cout << "Host #" << id() << ": sending packet (from: " << packet -> srcAddress().toString() << ", to: " << packet -> destAddress().toString() <<", " << packet -> dataString().length() << " bytes)" << std::endl;
  int n = rand() % links_.size();
  links_.at(n) -> link(this, packet);
}