#ifndef SIMULATOR_H
#define SIMULATOR_H

#define RANDOM_SEED 369369

#include <cstdlib>
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

class Simulator;

class Schedule {
private:
  double time_;
  std::function<void()> function_;

public:
  double time() { return time_; }
  void call() { function_(); }

  Schedule(double time, std::function<void()> function)
      : time_(time), function_(function) {}
  bool operator<(const Schedule s) const {return time_ > s.time_;}
};

class Simulator {
private:
  static double time_;
  static std::priority_queue<Schedule> pq_;
public:
  static double now() { return time_; }

  static void prepare() { srand(RANDOM_SEED); }
  static void schedule(double time, std::function<void()> function) {
    // 스케줄 큐에 스케줄을 추가한다.
    // TODO: 구현
    pq_.push(Schedule(time, function));
  }

  static void run() {
    // 모든 스케줄을 실행한다.
    // TODO: 구현
    while(!pq_.empty()){
      Schedule s = pq_.top();
      time_ = s.time();
      s.call();
      pq_.pop();
    }
  }
};

#endif