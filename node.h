#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;
protected:
  std::vector<Link *> links_;
  Packet *packet_;
public:
  Node() : id_(nextId_++) {}

  virtual ~Node();
  virtual void receive() = 0;

  int id() const { return id_; }
  void setPacket(Packet *packet);
  Packet *getPacket(){return packet_;}
  bool operator==(Node *a){return a -> id() == id_;}
  
};

#endif