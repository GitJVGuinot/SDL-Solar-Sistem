/// @author Javier Guinot Almenar
/// @file TimeCont.h

/////////////////////////
#ifndef __TIME_CONT_H__
#define __TIME_CONT_H__ 1
/////////////////////////

#include <iostream>
#include <chrono>
#include <algorithm>

const enum
{
  seconds = 0,
  milliseconds,
  microseconds,
  maxprecision,
  nanoseconds,
  picoseconds,
};

class TimeCont
{
private:
  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  std::chrono::time_point<std::chrono::steady_clock> end_time_;

public:
  static void Example();

  void startTime();

  // The next functions are only avaliable for the enums precisions
  // Each time are called take the new value for end_time_
  // and calculate the time between start_time_ & end_time_
  long long getElapsedTime(const int &precision);
  int printElapsedTime(const int &precision, char *str = nullptr);

};

/////////////////////////
#endif /* __TIME_CONT_H__ */
/////////////////////////
