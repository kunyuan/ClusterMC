#ifndef response_H
#define response_H

#include "abort.h"
#include <math.h>
namespace green {

// return the bare fermionic Green's function
// Ek=k^2-mu
/**
 * @brief the bare Fermionic Green's function
 * @param Ek k^2/2m-μ
 * @param tau (-beta, beta), exactly equal time is treated as 0^-
 */
template <typename T> T fermiGreen(T beta, T tau, T Ek) {
  ASSERT(tau > -beta && tau < beta, tau << " is out of the range!");
  T green = 1.0;
  if (tau == 0.0)
    tau = -1.0e-12;
  if (tau < 0.0) {
    // exactly equal time is treated as 0^-
    tau += beta;
    green *= -1.0;
  }

  T x = beta * Ek / 2.0;
  T y = 2.0 * tau / beta - 1.0;
  if (x > -100.0 && x < 100.0)
    green *= exp(-x * y) / (2.0 * cosh(x));
  else if (x > 100.0)
    green *= exp(-x * (y + 1.0));
  else
    green *= exp(x * (1.0 - y));

  ASSERT(isfinite(green), green);
  return green;
};

/**
 * @brief zero-temperature Fock diagram with a Yukawa type interaction
 *
 * @param k momentum
 * @param kF fermi momentum
 * @param mass Mass of the bosonic mode
 * @return fock diagram without a chemical-potential shift
 */

template <typename T> T fockYukawa(T k, T kF, T mass, bool shift = false) {
  // warning: this function only works for T=0!!!!
  T l = mass;
  T fock = 1.0 + l / kF * atan((k - kF) / l);
  fock -= l / kF * atan((k + kF) / l);
  fock -= (l * l - k * k + kF * kF) / 4.0 / k / kF *
          log((l * l + (k - kF) * (k - kF)) / (l * l + (k + kF) * (k + kF)));
  fock *= (-2.0 * kF) / M_PI;

  if (shift) {
    T shift = 1.0 - l / kF * atan(2.0 * kF / l);
    shift -= l * l / 4.0 / kF / kF * log(l * l / (l * l + 4.0 * kF * kF));
    shift *= (-2.0 * kF) / M_PI;
    fock = -shift;
  }

  ASSERT_ALLWAYS(isfinite(fock), fock);
  return fock;
  // return fock;
};

} // namespace green

#endif