#include "manual_router.h"
#include "router.h"

void ManualRouter::addRoutingEntry(const Address &destination, Link *nextLink){
  RoutingEntry entry;
  entry.destination = destination;
  entry.nextLink = nextLink;
  routingTable_.push_back(entry);
}