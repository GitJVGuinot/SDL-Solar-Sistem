/// @author Javier Guinot Almenar
/// @file time_cont.cc

#include <time_cont.h>
#include <thread>

/* 1 */  typedef std::ratio<1l, 1l> sec;
typedef std::chrono::duration<long long, sec> Seconds;
/* 4 */  typedef std::ratio<1l, 1000l> milli;
typedef std::chrono::duration<long long, milli> Milliseconds;
/* 7 */  typedef std::ratio<1l, 1000000l> micro;
typedef std::chrono::duration<long long, micro> Microseconds;
/* 8 */  typedef std::ratio<1l, 10000000l> max;
typedef std::chrono::duration<long long, max> Maxprecision;
/* 10 */ typedef std::ratio<1l, 1000000000l> nano;
typedef std::chrono::duration<long long, nano> Nanoseconds;
/* 13 */ typedef std::ratio<1l, 1000000000000l> pico;
typedef std::chrono::duration<long long, pico> Picoseconds;

void TimeCont::startTime()
{
  start_time_ = std::chrono::steady_clock::now();
}

long long TimeCont::getElapsedTime(const int &precision)
{
  end_time_ = std::chrono::steady_clock::now();
  switch (precision)
  {
    case seconds:
    auto elapsed_sec = std::chrono::duration_cast<Seconds>(end_time_ - start_time_);
    return elapsed_sec.count();
    case milliseconds:
    auto elapsed_milli = std::chrono::duration_cast<Milliseconds>(end_time_ - start_time_);
    return elapsed_milli.count();
    case microseconds:
    auto elapsed_micro = std::chrono::duration_cast<Microseconds>(end_time_ - start_time_);
    return elapsed_micro.count();
    case maxprecision:
    auto elapsed_max = std::chrono::duration_cast<Maxprecision>(end_time_ - start_time_);
    return elapsed_max.count();
    case nanoseconds:
    auto elapsed_nano = std::chrono::duration_cast<Nanoseconds>(end_time_ - start_time_);
    return elapsed_nano.count();
    case picoseconds:
    auto elapsed_pico = std::chrono::duration_cast<Picoseconds>(end_time_ - start_time_);
    return elapsed_pico.count();
    default: break;
  }
  return 0;
}

int TimeCont::printElapsedTime(const int &precision, char *str)
{
  end_time_ = std::chrono::steady_clock::now();

  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;

  switch (precision)
  {
    case seconds:
    auto elapsed_sec = std::chrono::duration_cast<Seconds>(end_time_ - start_time_);
    std::cout << elapsed_sec.count() << " second/s" << std::endl;
    break;
    case milliseconds:
    auto elapsed_milli = std::chrono::duration_cast<Milliseconds>(end_time_ - start_time_);
    std::cout << elapsed_milli.count() << " millisecond/s" << std::endl;
    break;
    case microseconds:
    auto elapsed_micro = std::chrono::duration_cast<Microseconds>(end_time_ - start_time_);
    std::cout << elapsed_micro.count() << " microsecond/s" << std::endl;
    break;
    case maxprecision:
    auto elapsed_max = std::chrono::duration_cast<Maxprecision>(end_time_ - start_time_);
    std::cout << elapsed_max.count() << " min-unit" << std::endl;
    break;
    case nanoseconds:
    auto elapsed_nano = std::chrono::duration_cast<Nanoseconds>(end_time_ - start_time_);
    std::cout << elapsed_nano.count() << " nanosecond/s" << std::endl;
    break;
    case picoseconds:
    auto elapsed_pico = std::chrono::duration_cast<Picoseconds>(end_time_ - start_time_);
    std::cout << elapsed_pico.count() << " picosecond/s" << std::endl;
    break;
  }
  return 1;
}

void TimeCont::Example()
{
  TimeCont timer;
  timer.startTime();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  timer.printElapsedTime(seconds);
  timer.printElapsedTime(milliseconds);
  timer.printElapsedTime(microseconds);
  timer.printElapsedTime(maxprecision);
  timer.printElapsedTime(nanoseconds);
  timer.printElapsedTime(picoseconds);

  std::cout << "Time: " << timer.getElapsedTime(seconds) << std::endl;
  std::cout << "Time: " << timer.getElapsedTime(milliseconds) << std::endl;
  std::cout << "Time: " << timer.getElapsedTime(microseconds) << std::endl;
  std::cout << "Time: " << timer.getElapsedTime(maxprecision) << std::endl;
  std::cout << "Time: " << timer.getElapsedTime(nanoseconds) << std::endl;
  std::cout << "Time: " << timer.getElapsedTime(picoseconds) << std::endl;
}
