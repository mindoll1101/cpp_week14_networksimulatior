#ifndef PACKET_SINK_SERVICE_H
#define PACKET_SINK_SERVICE_H

#include "service.h"
#include <string>

class PacketSinkService : public Service {
  friend class PacketSinkServiceInstaller;
private:
  int totalBytes_;
  PacketSinkService(Host *host, short port) : Service(host, port){};
  virtual std::string name(){return "PacketSinkService";}
public:
  void init(){
    totalBytes_ = 0;
  }
  void execute(Packet *packet){
    totalBytes_ += (int)packet -> data().size();
    std::string message = "received total " + std::to_string(totalBytes_) + " bytes";
    log(message);
    delete packet;
  }
};

#endif