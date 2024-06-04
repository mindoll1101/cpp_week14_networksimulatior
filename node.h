#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include "object.h"
#include <vector>

class Node : public Object{
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;
  virtual std::string name(){return "Node";}
protected:
  std::vector<Link *> links_;
  Packet *packet_;
public:
  Node() : id_(nextId_++), packet_(nullptr) {}

  virtual ~Node(){};
  virtual void receive(Packet *packet) = 0;

  int id() const { return id_; }
  void setPacket(Packet *packet);
  Packet *getPacket(){return packet_;}
  bool operator==(Node *a){return a -> id() == id_;}
  
};

#endif