#include "service_installer.h"
#include <iostream>
void ServiceInstaller::install(Host *host, Service *service){
  host -> services_.push_back(service);
}