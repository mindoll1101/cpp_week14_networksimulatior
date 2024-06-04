#ifndef AUTO_ROUTER_H
#define AUTO_ROUTER_H

#include "host.h"
#include "link.h"
#include "router.h"
#include "service.h"
#include <algorithm>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <iostream>

class AutoRouter : public Router {
private:
  std::vector<double> d;
  virtual std::string name(){return "AutoRouter";}
public:
  void calculate(const std::vector<Node *> &nodes,
                 const std::vector<Link *> &links) {
    // 전체 노드와 링크 정보를 통해
    // 모든 호스트로 전달될 수 있는 라우팅 테이블을 구성한다
    // TODO: 구현
    std::priority_queue<std::pair<Node *, double>> pq;
    std::vector<std::pair<Node *, Link *>> route;
    std::vector<std::pair<Address, Node *>> hosts;
    std::vector<std::pair<Node *, Link *>> *a = new std::vector<std::pair<Node *, Link *>>[nodes.size()];
    std::vector<std::pair<Node *, Link *>> *b = new std::vector<std::pair<Node *, Link *>>[nodes.size()];
    double INF = 10000000.0;
    for(size_t i = 0; i < nodes.size(); i++){
      d.push_back(INF);
      if(nodes[i] -> toString().find("<Host>") != std::string::npos){
        hosts.push_back(std::make_pair(dynamic_cast<Host *>(nodes[i]) -> address(), nodes[i]));
      }
      for(size_t j = 0; j < links.size(); j++){
        if(links[j] -> nodeA() == nodes[i] || links[j] -> nodeB() == nodes[i]){
          a[i].push_back(std::make_pair(links[j] -> other(nodes[i]), links[j]));
        }
      }
    }
    pq.push(std::make_pair(this, 0));
    d[this -> id()] = 0;
    while(!pq.empty()){
      Node *current = pq.top().first;
      double distance = -pq.top().second;
      pq.pop();
      if(d[current -> id()] < distance) continue;
      for(size_t i = 0; i < a[current -> id()].size(); i++){
        Node *next = a[current -> id()][i].first;
        Link *currentLink = a[current -> id()][i].second;
        double nextDistance = distance + currentLink -> delay();
        if(nextDistance < d[next -> id()]){
          d[next -> id()] = nextDistance;
          for(size_t j = 0; j < b[currentLink -> other(next) -> id()].size(); j++){
            b[next -> id()].push_back(b[currentLink -> other(next) -> id()][j]);
          }
          b[next -> id()].push_back(std::make_pair(current, currentLink));
          pq.push(std::make_pair(next, -nextDistance));
          route.push_back(std::make_pair(current, a[current -> id()][i].second));
        }
      }
    }
    for(size_t i = 0; i < hosts.size(); i++){
      for(size_t j = 0; j < b[hosts[i].second -> id()].size(); j++){
        RoutingEntry entry = {hosts[i].first, b[hosts[i].second -> id()][j].second};
        routingTable_.push_back(entry);
      }
    }
    a -> clear();
    delete a;
  }
};

#endif