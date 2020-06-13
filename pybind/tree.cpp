#include "global.h"
#include "propagator.h"
#include "vertex4.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
using namespace diag;
namespace py = pybind11;

PYBIND11_MODULE(vertex, m) {
  using namespace pybind11::literals;

  py::class_<parameter>(m, "parameter")
      .def(py::init<>())
      .def_readwrite("Order", &parameter::Order)
      .def_readwrite("Rs", &parameter::Rs)
      .def_readwrite("Mu", &parameter::Mu)
      .def_readwrite("Beta", &parameter::Beta);

  py::class_<propagator>(m, "propagator")
      .def(py::init<>())
      //       .def("green", &propagator::Green);
      .def("F", &propagator::F);

  //   py::class_<green>(m, "green")
  //       // .def("Size", &tauGrid::Size)
  //       .def(py::init<>())
  //       .def("size", &green::Size)
  //       .def("addTidxPair", &green::AddTidxPair)
  //       //  .def("evaluate", py::overload_cast<bool>(&green::Evaluate),
  //       //       "IsAnomal"_a = false)
  //       //  .def("evaluate",
  //       //       py::overload_cast<const momentum &, bool>(&green::Evaluate),
  //       //       "K"_a, "IsAnomal"_a = false)
  //       .def_readwrite("K", &green::K)
  //       .def_readwrite("Tpair", &green::_Tpair)
  //       .def_readwrite("weight", &green::_Weight);
}