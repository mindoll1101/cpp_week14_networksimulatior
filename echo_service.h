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
  Packet *packet_;
  EchoService(Host *host, short port) : Service(host, port) {}
  
public:
  ~EchoService();
  void init();
  void send();
  void execute();
};

#endif