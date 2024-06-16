#include "simulator.h"
#include "object.h"

double Simulator::time_ = 0.0;
std::priority_queue<Schedule> Simulator::pq_;

void Simulator::run() {
  Object::initializeAll();

  // 모든 스케줄을 실행한다.
  // TODO: 구현
  while(!pq_.empty()){
    Schedule s = pq_.top();
    time_ = s.time();
    s.call();
    pq_.pop();
  }
  Object::cleanup();
}