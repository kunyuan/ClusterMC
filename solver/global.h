#pragma once

#define FMT_HEADER_ONLY
#include "../lib/Eigen/Dense"
#include "../lib/abort.h"
#include "../lib/grid.h"
#include "../lib/utility.h"
#include <array>
#include <math.h>
#include <vector>

// comment to turn on all assert
// #define NDEBUG

enum DiagType { GAMMA, SIGMA, POLAR, DELTA };
typedef unsigned int uint;

///////////  Global Constants ////////////////////
const uint Dim = 3;      // dimensions, 2 or 3
const uint Spin = 2;     // spin index
const uint MaxOrder = 9; // Max diagram order
const uint MaxTauNum = MaxOrder + 1;
const uint MaxMomNum = MaxOrder + 3;

const DiagType diagtype = POLAR;
// typedef kFermiGrid kGrid; // for sigma
// typedef kBoseGrid kGrid; // for gamma, polar and delta

typedef Eigen::Matrix<double, Dim, 1> mom; // momentum vector
typedef Eigen::Vector2d verWeight; // direct and exchange weights for gamma

/////////// Global Parameter ////////////////////
struct Parameter {
  // physical parameters
  int order;
  double Rs, Ef, Kf;    // r_s, fermi energy, fermi momentum,
  double Nf, mu, beta;  // chemical potential, inverse temperature
  double mass2, lambda; // screening length^2, shift
  double charge2;       // screening length^2
  bool isboldG;
};

struct Variable {
  long long int counter; // counter to save the current MC step

  int order; // current order
  int scale;
  double absWeight; // current abs weight

  // external variables
  int extKidx;
  int extTidx;
  int extAngidx;

  // interval variables
  std::vector<mom> K;    // all momentum loop variables
  std::vector<double> T; // all tau variables
};

//////////   Generic Global Constants  /////////////////
const double TM32 = 1.0 / (pow(2.0, 32));
const double EPS = 1.0e-9;
const int MAXINT = 2147483647;
const int MININT = -2147483647;
const double π = 3.1415926535897932384626433832795;
const double MACHEPS = 2.22044604925031E-16; // Macheps + 1.0 > 1.0
const double MAXREAL = 1.0e30;
const double MINREAL = -1.0e30;

// enum spin { DOWN, UP };
// #define FLIPSPIN(x) spin(1 - x)
// Spin DOWN: 0,  Spin UP:1

// #define FLIP(x) (1 - x)

const int DOWN = 0, UP = 1;
const int IN = 0, OUT = 1;
const int LEFT = 0, RIGHT = 1;
const int INL = 0, OUTL = 1, INR = 2, OUTR = 3;
const int DIRECT = 0, EXCHANGE = 1;
const int DIR = 0, EX = 1;
const int HEAD = 0, TAIL = 1;

//////////////////////////////////////////////////////
