#include "global.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(parquetMC, m) {
  using namespace pybind11::literals;

  py::enum_<DiagType>(m, "DiagType", py::arithmetic())
      .value("GAMMA", GAMMA)
      .value("SIGMA", SIGMA)
      .value("POLAR", POLAR)
      .value("DELTA", DELTA);

  py::class_<Parameter>(m, "Parameter")
      .def(py::init<>())
      .def_readwrite("order", &Parameter::order)
      .def_readwrite("Rs", &Parameter::Rs)
      .def_readwrite("Kf", &Parameter::Kf)
      .def_readwrite("Ef", &Parameter::Ef)
      .def_readwrite("mu", &Parameter::mu)
      .def_readwrite("beta", &Parameter::beta)
      .def_readwrite("mass2", &Parameter::mass2)
      .def_readwrite("lambda", &Parameter::lambda)
      .def_readwrite("charge2", &Parameter::charge2)
      .def_readwrite("isboldG", &Parameter::isboldG);

  py::class_<Variable>(m, "Variable")
      .def(py::init<>())
      .def_readwrite("counter", &Variable::counter)
      .def_readwrite("order", &Variable::order)
      .def_readwrite("scale", &Variable::scale)
      .def_readwrite("absWeight", &Variable::absWeight)
      .def_readwrite("extKidx", &Variable::extKidx)
      .def_readwrite("extTidx", &Variable::extTidx)
      .def_readwrite("extAngidx", &Variable::extAngidx)
      .def_readwrite("K", &Variable::K)
      .def_readwrite("T", &Variable::T);

  // py::class_<propagator>(m, "propagator")
  //     .def(py::init<>())
  //     //       .def("green", &propagator::Green);
  //     .def("F", &propagator::F);

  {
      // diagram contruction classes
      // using namespace diag;
      // py::class_<green>(m, "green")
      //     // .def("Size", &tauGrid::Size)
      //     .def(py::init<>())
      //     .def("Size", &green::Size)
      //     .def("AddTidxPair", &green::AddTidxPair)
      //     .def_readwrite("K", &green::K)
      //     .def_readwrite("Tpair", &green::_Tpair)
      //     .def_readwrite("Weight", &green::_Weight);

      // py::enum_<channel>(m, "channel", py::arithmetic(), "channel
      // enumeration")
      //     .value("I", I, "fully irreducible channel except the bare
      //     interaction") .value("T", T, "particle-hole channel") .value("U",
      //     U, "particle-hole exchange channel") .value("S", S,
      //     "particle-particle channel") .value("TC", TC, "particle-hole
      //     counter channel") .value("UC", UC, "particle-hole exchange counter
      //     channel");

      // py::class_<vertex4>(m, "vertex4")
      //     .def(py::init<>())
      //     .def("Build", &vertex4::Build, "level"_a, "order"_a, "Kidx"_a,
      //     "Tidx"_a,
      //          "chan"_a, "side"_a)
      //     .def("TauNum", &vertex4::TauNum)
      //     .def("LoopNum", &vertex4::LoopNum)
      //     .def_readwrite("Tpair", &vertex4::Tpair)
      //     .def_readwrite("Weight", &vertex4::Weight)
      //     .def_readwrite("Channel", &vertex4::Channel)
      //     .def_readwrite("Level", &vertex4::Level)
      //     .def_readwrite("Side", &vertex4::Side)
      //     .def_readwrite("Order", &vertex4::Order)
      //     .def_readwrite("Tidx", &vertex4::Tidx)
      //     .def_readwrite("Kidx", &vertex4::LoopIdx)
      //     .def_readwrite("G", &vertex4::G)
      //     .def_readwrite("UST", &vertex4::_UST);

      // py::class_<bubble>(m, "bubble")
      //     .def(py::init<>())
      //     .def_readwrite("Channel", &bubble::Channel)
      //     .def_readwrite("LVer", &bubble::LVer)
      //     .def_readwrite("RVer", &bubble::RVer)
      //     .def_readwrite("Map", &bubble::Map);
  }

  {
    // using namespace mc;
    // py::class_<markov>(m, "markov").def(py::init<>());
    // .def("ChangeTau", &markov::ChangeTau);
  }
}