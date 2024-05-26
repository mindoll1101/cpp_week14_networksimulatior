#include "echo_service_installer.h"

// 호스트에 EchoService를 설치한다.
EchoService *EchoServiceInstaller::install(Host *host){
  echo_ = new EchoService(host, (int)listenPort_);
  this -> ServiceInstaller::install(host, echo_);
  return echo_;
}