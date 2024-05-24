#include "message_service_installer.h"

// 호스트에 MessageService를 설치한다
MessageService *MessageServiceInstaller::install(Host *host){
  message_ = new MessageService(host, 0, destAddress_, destPort_);
  this -> ServiceInstaller::install(host, message_);
  return message_;
}