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
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdio.h>
#include <string>

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

// inline std::string message(const std::string &msg) {
//   std::ostringstream o;
//   o << "@[" << __FILE__ << ":" << __LINE__ << "]: " << msg;
//   return o.str();
// }

#define ABORT(msg)                                                             \
  {                                                                            \
    std::ostringstream o;                                                      \
    o << "@[" << __FILE__ << ":" << __LINE__ << "]: " << msg;                  \
    throw std::runtime_error(o.str());                                         \
  }

#define ASSERT_ALLWAYS(condition, msg)                                         \
  do {                                                                         \
    if ((condition) == false)                                                  \
      ABORT(#condition << " fails: " << msg << std::endl);                     \
  } while (0)

// ASSERT will turn off when NDEBUG is on
#ifdef NDEBUG
#define ASSERT(condition, msg) ((void)0)
#else
#define ASSERT(condition, msg) ASSERT_ALLWAYS(condition, msg);
#endif

#endif /* defined(__Fermion_Simulator__error_handler__) */
