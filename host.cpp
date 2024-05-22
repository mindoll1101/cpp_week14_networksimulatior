#include "host.h"

void installService(Service *service){
  install(this, service);
  services_.push_back(service);
}

// 호스트와 설치된 서비스를 전부 초기화한다.
void initialize(){
  services_.clear();
}

// 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
void send(Packet *packet){
  
}