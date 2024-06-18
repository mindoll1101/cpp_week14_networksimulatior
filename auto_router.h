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
    std::priority_queue<std::pair<int, double>> pq;
    std::vector<Node *> hosts;
    std::vector<std::pair<int, Link *>> *vertex = new std::vector<std::pair<int, Link *>>[nodes.size()];
    std::vector<Link *> *route = new std::vector<Link *>[nodes.size()];

    double INF = 10000000.0;
    for(size_t i = 0; i < nodes.size(); i++){
      d.push_back(INF);
      if(nodes[i] -> toString().find("<Host>") != std::string::npos || nodes[i] -> toString().find("<Nat>") != std::string::npos){
        hosts.push_back(nodes[i]);
      }
      for(size_t j = 0; j < links.size(); j++){
        if(links[j] -> nodeA() == nodes[i] || links[j] -> nodeB() == nodes[i]){
          vertex[i].push_back(std::make_pair(std::find(nodes.begin(), nodes.end(), links[j] -> other(nodes[i])) - nodes.begin(), links[j]));
        }
      }
    }
    int current = std::find(nodes.begin(), nodes.end(), this) - nodes.begin();
    pq.push(std::make_pair(current, 0));
    d[current] = 0;
    while(!pq.empty()){
      current = pq.top().first;
      double distance = -pq.top().second;
      pq.pop();
      if(d[current] < distance) continue;
      for(size_t i = 0; i < vertex[current].size(); i++){
        int next = vertex[current][i].first;
        Link *currentLink = vertex[current][i].second;
        double nextDistance = distance + currentLink -> delay();
        if(nextDistance < d[next]){
          d[next] = nextDistance;
          route[next].clear();
          for(size_t j = 0; j < route[current].size(); j++){
            route[next].push_back(route[current][j]);
          }
          route[next].push_back(currentLink);
          pq.push(std::make_pair(next, -nextDistance));
        }
      }
    }
    for(size_t i = 0; i < hosts.size(); i++){
      current = std::find(nodes.begin(), nodes.end(), hosts[i]) - nodes.begin();
      RoutingEntry entry = {nodes[current] -> address(), route[current][0]};
      routingTable_.push_back(entry);
    }
    vertex -> clear();
    route -> clear();
    delete vertex;
    delete route;
  }
};

#endif