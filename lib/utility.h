//---------------------------------------------------------------------------
// �Nikolai V. Shokhirev, 2004-2008  <nikolai@shokhirev.com>
// http://www.shokhirev.com/nikolai.html
// Reduced demo version
//---------------------------------------------------------------------------

#ifndef MathUtils_H
#define MathUtils_H

// #include "abort.h"
#include "stdio.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <sstream>
#include <string>

//---------------------------------------------------------------------------
const double eps0 = 1.0e-10;

// FORTRAN abs
// double fabs(double x); // { return ( (x >= 0.0) ? x : -x); }

// FORTRAN iabs
// int iabs(int x); // { return ( (x >= 0.0) ? x : -x); }
// more functions ...

// float iszero
inline bool IsZero(double x, double eps = eps0) { return (fabs(x) < eps); }

// float equal
inline bool IsEqual(double x1, double x2, double eps = eps0) {
  return (fabs(x1 - x2) < eps);
}
inline bool IsEqual(uint x1, uint x2, double eps = eps0) { return x1 == x2; }
inline bool IsEqual(int x1, int x2, double eps = eps0) { return x1 == x2; }

template <typename T>
bool IsEqual(const T *x1, const T *x2, uint num, double eps = eps0) {
  for (uint i = 0; i < num; i++)
    if (!Equal(x1[i], x2[i], eps0))
      return false;
  return true;
}

template <typename T> std::string ToString(const T &value) {
  std::ostringstream oss;
  oss << value;
  return oss.str();
}

template <typename T> std::string ToString(const T *array, size_t Num) {
  std::ostringstream oss;
  oss << "[";
  for (size_t i = 0; i < Num; i++)
    oss << " " << array[i] << ",";
  oss << "]";
  return oss.str();
}

template <typename T> void AssignFromTo(T *source, T *target, int size) {
  for (int i = 0; i < size; i++)
    target[i] = source[i];
}

template <typename T> void InitialArray(T *target, T t, const int &size) {
  for (int i = 0; i < size; i++)
    target[i] = t;
}

inline bool CleanFile(const std::string &FileName) {
  std::ofstream ofs(FileName, std::ofstream::out | std::ofstream::trunc);
  if (ofs.is_open()) {
    ofs.close();
    return true;
  } else {
    ofs.close();
    return false;
  }
}

inline bool DoesFileExist(const std::string &FileName) {
  std::ofstream ofs(FileName, std::ofstream::in);
  if (ofs.is_open()) {
    ofs.close();
    return true;
  } else {
    ofs.close();
    return false;
  }
}

// #define CHECKNULL(source)                                                      \
//   {                                                                            \
//     if ((source) == nullptr)                                                   \
//       ABORT(#source << " is nullptr!");                                        \
//   }

// template <typename... TS>
// static std::string Format(std::string format, TS... args) {
//   char format_buffer[512];
//   int length = sprintf(format_buffer, format.c_str(), args...);
//   ASSERT_ALLWAYS(length > 0, "Failed to construct the string!");
//   return std::string(format_buffer, length);
// }

// calculate A^B at the compile time
template <int A, int B> struct get_power {
  static const int value = A * get_power<A, B - 1>::value;
};
template <int A> struct get_power<A, 0> { static const int value = 1; };

/**
 * Remove surrounding whitespace from a std::string.
 * @param s The string to be modified.
 * @param t The set of characters to delete from each end
 * of the string.
 * @return The same string passed in as a parameter reference.
 */
inline std::string &trim(std::string &s, const char *t = " \t\n\r\f\v") {
  s.erase(0, s.find_first_not_of(t));
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

inline std::string ProgressBar(double progress) {
  std::ostringstream oss;
  int barWidth = 70;

  oss << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      oss << "I";
    else if (i == pos)
      oss << "I";
    else
      oss << " ";
  }
  oss << "] " << int(progress * 100.0) << " %\r";
  oss.flush();
  return oss.str();
}

inline std::stringstream GetLine(std::ifstream &File) {
  std::string line;
  while (true) {
    std::getline(File, line);
    line = trim(line);
    if (line.size() > 0 && line[0] != '#') {
      std::replace(line.begin(), line.end(), ',', ' ');
      return std::stringstream(line);
    }
  }
}

class InterruptHandler {
public:
  InterruptHandler() {
    __IsDelaying = false;
    __Signal = -1;
    signal(SIGINT, __SignalHandler);
    signal(SIGTERM, __SignalHandler);
  };
  ~InterruptHandler() {
    signal(SIGINT, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
  };
  void Delay() {
    signal(SIGINT, __DelayedSignalHandler);
    signal(SIGTERM, __DelayedSignalHandler);
    __IsDelaying = true;
  };
  void Resume() {
    signal(SIGINT, __SignalHandler);
    signal(SIGTERM, __SignalHandler);
    if (__IsDelaying && (__Signal == SIGINT || __Signal == SIGTERM)) {
      __SignalHandler(__Signal);
      __Signal = -1;
      __IsDelaying = false;
    }
  };
  bool IsDelaying() { return __IsDelaying; }

private:
  // signal handler for normal state
  static void __SignalHandler(int signum) {
    __Signal = signum;
    exit(signum);
  }
  // signal handler after Delay() is called
  static void __DelayedSignalHandler(int signum) { __Signal = signum; };
  bool __IsDelaying;
  static int __Signal;
};
#endif