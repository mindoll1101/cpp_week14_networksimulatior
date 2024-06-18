#ifndef BULK_SEND_SERVICE_H
#define BULK_SEND_SERVICE_H
// https://www.diffchecker.com/2idqlhXi/
#include "host.h"
#include "service.h"
#include "simulator.h"
#include <vector>
#include <iostream>

#define CLIENT_PORT 1000
#define PACKET_SIZE 512

class BulkSendService : Service {
  friend class BulkSendServiceInstaller;

private:
  Packet *packet_;
  Address destAddress_;
  short destPort_;
  double delay_;
  double startTime_;
  double stopTime_;
  std::vector<Packet *> packets_;
  std::string data_;
  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0)
     : Service(host, CLIENT_PORT), destAddress_(destAddress), destPort_(destPort), delay_(delay), startTime_(startTime), stopTime_(stopTime){}
  virtual std::string name(){return "BulkSendService";}
public:
  void initialize(){
    std::vector <Service *> services = host_ -> getServices();
    short port = CLIENT_PORT;
    for(int i = 0; i < (int)services.size(); i++){
      if(services[i] -> getPort() == port){
        port++;
      }
    }
    data_ = "";
    for(int i = 0; i < PACKET_SIZE; i++){
      data_ += "A";
    }
    port_ = port;
    packet_ = nullptr;
    std::function<void()> fptr = [this](){this -> send();};
    Simulator::schedule(startTime_, fptr);
  }
  void send(){
    startTime_ += delay_;
    Packet *packet = new Packet(host_ -> address(), destAddress_, port_, destPort_, data_);
    std::string message = "sending data";
    log(message);
    host_ -> send(packet);
    std::function<void()> fptr = [this](){this -> send();};
    if(startTime_ < stopTime_)
      Simulator::schedule(startTime_, fptr);
  }
  void execute(Packet *packet){}
};

#endif