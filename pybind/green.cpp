#include "../lib/green.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace green;
PYBIND11_MODULE(green, m) {
  // m.def("fermiGreen",
  //       py::overload_cast<double, double, double>(&fermiGreen<double>),
  //       "bare fermionic Green's function");
  m.def("fermiGreen", &fermiGreen<double>, "bare fermionic Green's function");
  m.def("fockYukawa", &fockYukawa<double>,
        "zero temperature Yukawa interaction Fock diagram");
}
