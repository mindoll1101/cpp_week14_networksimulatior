#ifndef PING_SERVICE_INSTALLER_H
#define PING_SERVICE_INSTALLER_H

#include "address.h"
#include "message_service.h"
#include "service_installer.h"

class MessageServiceInstaller : public ServiceInstaller {
private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;
  MessageService *message_;

public:
  MessageServiceInstaller(const Address &destAddress, short destPort)
      : destAddress_(destAddress), destPort_(destPort) {}

  // 호스트에 MessageService를 설치한다
  MessageService *install(Host *host){
    std::vector <Service *> services = host -> getServices();
    short port = CLIENT_PORT;
    for(int i = 0; i < (int)services.size(); i++){
      if(services[i] -> getPort() == port){
        port++;
      }
    }
    message_ = new MessageService(host, port, destAddress_, destPort_);
    ServiceInstaller::install(host, message_);
    return message_;
  }
};

#endif