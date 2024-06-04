#ifndef LINK_H
#define LINK_H

#include "object.h"
#include "packet.h"
#include <cstdlib>
#include <vector>

class Node;

class Link : public Object {
  friend class LinkInstaller;

private:
  Link(Node *nodeA, Node *nodeB, double delay = 0.0)
      : nodeA_(nodeA), nodeB_(nodeB), delay_(delay), sendCount_(0) {}
  virtual std::string name(){return "Link";}
  Node *nodeA_;
  Node *nodeB_;
  double delay_;
  std::vector<std::pair<Node *, Packet *>> packets_;
  int sendCount_;
public:
  ~Link(){}
  void link(Node *node, Packet *packet);

  void packetOut();

  double delay() { return delay_; }

  Node *nodeA() { return nodeA_; }

  Node *nodeB() { return nodeB_; }

  // 매개변수로 주어진 노드가 아닌 반대편 노드를 구한다.
  Node *other(const Node *node) const {
    return node == nodeA_ ? nodeB_ : nodeA_;
  }
};

#endif  