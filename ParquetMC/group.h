#pragma once
#include "global.h"
#include <string>
#include <vector>

namespace diag {
using namespace std;

class Group {
public:
  // Group(){};
  // parameter &p;
  // variable &var;
  size_t order;
  size_t loopNum;
  size_t tauNum;
  string name;
  double reweight;

  ////// MC update /////////////////
  // virtual double propOrder() = 0;
  // virtual double propK() = 0;
  // virtual double propT() = 0;
  // virtual double propExtK() = 0;
  // virtual double propExtT() = 0;

  // virtual void rejectOrder() = 0;
  // virtual void rejectK() = 0;
  // virtual void rejectT() = 0;
  // virtual void rejectExtK() = 0;
  // virtual void rejectExtT() = 0;

  // evaluate();

  // private:
};

} // namespace diag