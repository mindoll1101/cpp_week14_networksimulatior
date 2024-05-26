#include "message_service_installer.h"
#include <iostream>
// 호스트에 MessageService를 설치한다
MessageService *MessageServiceInstaller::install(Host *host){
  message_ = new MessageService(host, CLIENT_PORT + host -> getServicesCount(), destAddress_, destPort_);
  this -> ServiceInstaller::install(host, message_);
  return message_;
}