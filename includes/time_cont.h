/// @author Javier Guinot Almenar
/// @file TimeCont.h

/////////////////////////
#ifndef __TIME_CONT_H__
#define __TIME_CONT_H__ 1
/////////////////////////

#include <iostream>
#include <chrono>
#include <algorithm>

class TimeCont
{
private:
  std::chrono::time_point<std::chrono::steady_clock> start_time_;
  std::chrono::time_point<std::chrono::steady_clock> end_time_;

public:

  void startTime();

  void endTime();

  // Use 10l to 0.1, 100l to 0.01 ... to set the precision in the template
  // Example
  // TimeCont time;
  // time.printElapsedTime<1000l>();
  // that significate a precision of 0.001 -> 1678 units = 1.678 sec
  /*
  template <typename precision>
  void printElapsedTime(char* str = nullptr);
  */
  void printElapsedSeconds(char* str = nullptr);

  void printElapsedMilliseconds(char* str = nullptr);

  void printElapsedMicroseconds(char* str = nullptr);

  void printElapsedMaxPrecision(char* str = nullptr);

  void printElapsedNanoseconds(char* str = nullptr);

  void printElapsedPicoseconds(char* str = nullptr);

  // This is going to wait for 100 milliseconds = 0.1 second
  static void Example();
};

/////////////////////////
#endif /* __TIME_CONT_H__ */
/////////////////////////
