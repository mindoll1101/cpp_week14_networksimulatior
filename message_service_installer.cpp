#include "message_service_installer.h"
#include <iostream>
#include <vector>
// 호스트에 MessageService를 설치한다
MessageService *MessageServiceInstaller::install(Host *host){
  std::vector <Service *> services = host -> getServices();
  int port = CLIENT_PORT;
  for(int i = 0; i < (int)services.size(); i++){
    if(services[i] -> getPort() == port){
      port++;
    }
  }
  message_ = new MessageService(host, port, destAddress_, destPort_);
  this -> ServiceInstaller::install(host, message_);
  return message_;
}