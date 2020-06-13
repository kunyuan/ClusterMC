//
// Created by Kun Chen on 10/5/14.
// Copyright (c) 2014 Kun Chen. All rights reserved.
//

#ifndef __timer_H_
#define __timer_H_

#include <ctime>
#include <iomanip>
#include <iosfwd>

class timer {
  //   friend std::ostream &operator<<(std::ostream &os, timer &t);
  //===========================================================================
  // Allow timers to be printed to ostreams using the syntax 'os << t'
  // for an ostream 'os' and a timer 't'.  For example, "cout << t" will
  // print out the total amount of time 't' has been "running".

  friend std::ostream &operator<<(std::ostream &os, timer &t) {
    os << std::setprecision(2) << std::setiosflags(std::ios::fixed)
       << t.acc_time + (t.running ? t.elapsed_time() : 0);
    return os;
  }

private:
  bool running;
  clock_t start_clock;
  time_t start_time;
  double acc_time;
  //===========================================================================
  // Return the total time that the timer has been in the "running"
  // state since it was first "started" or last "restarted".  For
  // "short" time periods (less than an hour), the actual cpu time
  // used is reported instead of the elapsed time.

  double elapsed_time() {
    time_t acc_sec = time(0) - start_time;
    if (acc_sec < 3600)
      return (clock() - start_clock) / (1.0 * CLOCKS_PER_SEC);
    else
      return (1.0 * acc_sec);

  } // timer::elapsed_time

public:
  // 'running' is initially false.  A timer needs to be explicitly started
  // using 'start' or 'restart'
  timer() : running(false), start_clock(0), start_time(0), acc_time(0) {}

  //   void start(const char *msg = 0);
  //===========================================================================
  // Start a timer.  If it is already running, let it continue running.
  // Print an optional message.

  void start() {
    // Return immediately if the timer is already running
    if (running)
      return;

    // Set timer status to running and set the start time
    running = true;
    start_clock = clock();
    start_time = time(0);

  } // timer::start
  //   void restart(const char *msg = 0);
  //===========================================================================
  // Turn the timer off and start it again from 0.  Print an optional message.

  void restart() {
    // Set timer status to running, reset accumulated time, and set start time
    running = true;
    acc_time = 0;
    start_clock = clock();
    start_time = time(0);

  } // timer::restart

  //   void stop(const char *msg = 0);
  //===========================================================================
  // Stop the timer and print an optional message.

  void stop() {
    // Compute accumulated running time and set timer status to not running
    if (running)
      acc_time += elapsed_time();
    running = false;

  } // timer::stop

  bool check(time_t Interval) {
    time_t acc_sec = time(0) - start_time;
    if (acc_sec < Interval)
      return false;
    else {
      restart();
      return true;
    }
  }

}; // class timer

#endif //__timer_H_
