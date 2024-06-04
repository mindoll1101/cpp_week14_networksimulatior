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
  BulkSendService(Host *host, Address destAddress, short destPort,
                  double delay = 1, double startTime = 0,
                  double stopTime = 10.0)
     : Service(host, CLIENT_PORT), destAddress_(destAddress), destPort_(destPort), delay_(delay), startTime_(startTime), stopTime_(stopTime){}
  virtual std::string name(){return "BulkSendService";}
public:
  ~BulkSendService(){
    for(size_t i = 0; i < packets_.size(); i++){
      delete packets_[i];
    }
  }
  void init(){
    std::vector <Service *> services = host_ -> getServices();
    short port = CLIENT_PORT;
    for(int i = 0; i < (int)services.size(); i++){
      if(services[i] -> getPort() == port){
        port++;
      }
    }
    Service::port_ = port;
    packet_ = nullptr;
    std::function<void()> fptr = [this](){this -> send();};
    Simulator::schedule(startTime_, fptr);
    stopTime_ -= startTime_;
    startTime_ += delay_;
  }
  void send(){
    std::vector<char> data(512);
    if(stopTime_ > 0.0){
      packet_ = new Packet(host_ -> address(), destAddress_, Service::port_, destPort_, data);
      std::function<void()> fptr = [this](){this -> send();};
      Simulator::schedule(startTime_, fptr);
      packets_.push_back(packet_);
      stopTime_ -= delay_;
      startTime_ += delay_;
      execute(packet_);
    }
  }
  void execute(Packet *packet){
    std::string message = "sending data";
    log(message);
    host_ -> send(packet);
  }
};

#endif