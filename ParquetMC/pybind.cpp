#include "global.h"
#include "propagator.h"
#include "vertex4.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
using namespace diag;
namespace py = pybind11;

PYBIND11_MODULE(parquetMC, m) {
  using namespace pybind11::literals;

  py::class_<parameter>(m, "parameter")
      .def(py::init<>())
      .def_readwrite("Order", &parameter::Order)
      .def_readwrite("Rs", &parameter::Rs)
      .def_readwrite("Mu", &parameter::Mu)
      .def_readwrite("Beta", &parameter::Beta)
      .def_readwrite("Kf", &parameter::Kf)
      .def_readwrite("Ef", &parameter::Ef)
      .def_readwrite("Mass2", &parameter::Mass2)
      .def_readwrite("Lambda", &parameter::Lambda)
      .def_readwrite("Charge2", &parameter::Charge2)
      .def_readwrite("TotalStep", &parameter::TotalStep)
      .def_readwrite("ReWeight", &parameter::ReWeight)
      .def_readwrite("PrintTimer", &parameter::PrintTimer)
      .def_readwrite("SaveTimer", &parameter::SaveTimer)
      .def_readwrite("MessageTimer", &parameter::MessageTimer)
      .def_readwrite("ReweightTimer", &parameter::ReweightTimer);

  py::class_<variable>(m, "variable")
      .def(py::init<>())
      .def_readwrite("Counter", &variable::Counter)
      .def_readwrite("CurrOrder", &variable::CurrOrder)
      .def_readwrite("CurrAbsWeight", &variable::CurrAbsWeight)
      .def_readwrite("CurrExtMomBin", &variable::CurrExtMomBin)
      .def_readwrite("CurrExtTauBin", &variable::CurrExtTauBin)
      .def_readwrite("CurrExtAngBin", &variable::CurrExtAngBin)
      .def_readwrite("LoopMom", &variable::LoopMom)
      .def_readwrite("Tau", &variable::Tau);

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