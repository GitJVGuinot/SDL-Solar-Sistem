/// @author Javier Guinot Almenar
/// @file time_cont.cc

#include <time_cont.h>
#include <thread>

typedef std::ratio<1l, 1l> sec;
typedef std::chrono::duration<long long, sec> seconds;
typedef std::ratio<1l, 1000l> mili;
typedef std::chrono::duration<long long, mili> milliseconds;
typedef std::ratio<1l, 1000000l> micro;
typedef std::chrono::duration<long long, micro> microseconds;
typedef std::ratio<1l, 10000000l> max;
typedef std::chrono::duration<long long, max> maxprecision;
typedef std::ratio<1l, 1000000000l> nano;
typedef std::chrono::duration<long long, nano> nanoseconds;
typedef std::ratio<1l, 1000000000000l> pico;
typedef std::chrono::duration<long long, pico> picoseconds;

void TimeCont::startTime()
{
  start_time_ = std::chrono::steady_clock::now();
}

void TimeCont::endTime()
{
  end_time_ = std::chrono::steady_clock::now();
}

void TimeCont::printElapsedSeconds(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<seconds>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " second/s" << std::endl;
}

void TimeCont::printElapsedMilliseconds(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<milliseconds>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " millisecond/s" << std::endl;
}

void TimeCont::printElapsedMicroseconds(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<microseconds>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " microsecond/s" << std::endl;
}

void TimeCont::printElapsedMaxPrecision(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<maxprecision>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " min-unit" << std::endl;
}

void TimeCont::printElapsedNanoseconds(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<nanoseconds>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " nanosecond/s" << std::endl;
}

void TimeCont::printElapsedPicoseconds(char* str)
{
  auto elapsed_time = std::chrono::duration_cast<picoseconds>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time.count() << " picosecond/s" << std::endl;
}

/*
template <typename precision>
void TimeCont::printElapsedTime(char* str)
{
  typedef std::ratio<1l, precision> var;
  typedef std::chrono::duration<long long, var> variable;

  auto elapsed_time_ = std::chrono::duration_cast<variable>(end_time_ - start_time_);
  if(str == nullptr) std::cout << "Elapsed time: ";
  else std::cout << str;
  std::cout << elapsed_time_.count() << " second/s" << std::endl;
}
*/

void TimeCont::Example()
{
  TimeCont timer;
  timer.startTime();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  timer.endTime();
  timer.printElapsedSeconds();
  timer.printElapsedMilliseconds();
  timer.printElapsedMicroseconds();
  timer.printElapsedNanoseconds();
  timer.printElapsedPicoseconds();
}
