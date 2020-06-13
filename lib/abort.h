//
//  error_handler.h
//  Fermion_Simulator
//
//  Created by Kun Chen on 10/11/14.
//  Copyright (c) 2014 Kun Chen. All rights reserved.
//

#ifndef __FeynCalc__error_handler__
#define __FeynCalc__error_handler__

#include <csignal>
#include <cstdlib>
#include <stdexcept>

// #define EXCEPTION(name)                                                        \
//   class name : public std::runtime_error {                                     \
//   public:                                                                      \
//     name(const std::string &msg) : std::runtime_error(msg) {}                  \
//   };

// EXCEPTION(NOTIMPLEMENTED);
// EXCEPTION(IOInvalid);
// EXCEPTION(TypeInvalid);
// EXCEPTION(KeyInvalid);
// EXCEPTION(ValueInvalid);
// EXCEPTION(IndexInvalid);
// EXCEPTION(MemoryException);
// EXCEPTION(RunTimeException);

// std::ostringstream __stream_more__;
// __stream_more__ << "@[" << __FILE__ << ":" << __LINE__ << "] " << ss.str();
// throw exception(__stream_more__.str());

// #define THROW_ERROR(exception, msg) THROW(exception, msg, ERROR)

// #define THROW(msg, priority)                                                   \
//   do {                                                                         \
//     LOGGER(priority, "Exception throwed: " << msg << "\n@[" << __FILE__ << ":" \
//                                            << __LINE__ << "] ");               \
//     std::abort();                                                              \
//   } while (0)

// #define ABORT(msg) THROW(msg, ERROR)

#define ABORT(msg)                                                             \
  throw std::runtime_error(msg " @[" `__FILE__` ":" `__LINE__` "]");

#define ASSERT_ALLWAYS(condition, msg)                                         \
  do {                                                                         \
    if ((condition) == false)                                                  \
      ABORT(#condition " does not hold! " msg);                                \
  } while (0)

// ASSERT will turn off when NDEBUG is on
#ifdef NDEBUG
#define ASSERT(condition, msg) ((void)0)
#else
#define ASSERT(condition, msg) ASSERT_ALLWAYS(condition, msg);
#endif

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

#endif /* defined(__Fermion_Simulator__error_handler__) */
