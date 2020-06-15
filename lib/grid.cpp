#include "grid.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace grid;
PYBIND11_MODULE(grid, m) {
  using namespace pybind11::literals;
  py::class_<Tau>(m, "Tau")
      // .def("Size", &tauGrid::Size)
      .def(py::init<>())
      .def("build", &Tau::build, "Build Tau Grid", "beta"_a, "size"_a,
           "scale"_a)
      .def("floor", &Tau::floor)
      .def("str", &Tau::str)
      .def_readwrite("size", &Tau::size)
      .def_readwrite("grid", &Tau::grid)
      .def_readwrite("weight", &Tau::weight);

  py::class_<FermiK>(m, "FermiK")
      // .def("Size", &tauGrid::Size)
      .def(py::init<>())
      .def("build", &FermiK::build, "Build fermionic K Grid", "kF"_a, "maxK"_a,
           "size"_a, "scale"_a)
      .def("floor", &FermiK::floor)
      .def("str", &FermiK::str)
      .def_readwrite("size", &FermiK::size)
      .def_readwrite("kFidx", &FermiK::kFidx)
      .def_readwrite("grid", &FermiK::grid);

  py::class_<BoseK>(m, "BoseK")
      // .def("Size", &tauGrid::Size)
      .def(py::init<>())
      .def("build", &BoseK::build, "Build bosonic K Grid", "kF"_a, "maxK"_a,
           "size"_a, "scale"_a)
      .def("floor", &BoseK::floor)
      .def("str", &BoseK::str)
      .def_readwrite("size", &BoseK::size)
      .def_readwrite("kFidx", &BoseK::kFidx)
      .def_readwrite("twokFidx", &BoseK::twokFidx)
      .def_readwrite("grid", &BoseK::grid);

  py::class_<Uniform>(m, "Uniform")
      // .def("Size", &tauGrid::Size)
      .def(py::init<>())
      .def("build", &Uniform::build, "Build uniform grid", "bounds"_a, "size"_a)
      .def("floor", &Uniform::floor)
      .def("str", &Uniform::str)
      .def_readwrite("size", &Uniform::size)
      .def_readwrite("grid", &Uniform::grid);
}