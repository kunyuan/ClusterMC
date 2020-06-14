#include "global.h"
#include "markov.h"
#include "propagator.h"
#include "vertex4.h"
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
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
      .def_readwrite("ReweightTimer", &parameter::ReweightTimer)
      .def_readwrite("TauGrid", &parameter::TauGrid)
      .def_readwrite("FermiKGrid", &parameter::FermiKGrid)
      .def_readwrite("BoseKGrid", &parameter::BoseKGrid)
      .def_readwrite("AngleGrid", &parameter::AngleGrid);

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

  // py::class_<propagator>(m, "propagator")
  //     .def(py::init<>())
  //     //       .def("green", &propagator::Green);
  //     .def("F", &propagator::F);

  { // diagram contruction classes
    using namespace diag;
    py::class_<green>(m, "green")
        // .def("Size", &tauGrid::Size)
        .def(py::init<>())
        .def("Size", &green::Size)
        .def("AddTidxPair", &green::AddTidxPair)
        //  .def("evaluate", py::overload_cast<bool>(&green::Evaluate),
        //       "IsAnomal"_a = false)
        //  .def("evaluate",
        //       py::overload_cast<const momentum &, bool>(&green::Evaluate),
        //       "K"_a, "IsAnomal"_a = false)
        .def_readwrite("K", &green::K)
        .def_readwrite("Tpair", &green::_Tpair)
        .def_readwrite("Weight", &green::_Weight);

    py::enum_<channel>(m, "channel", py::arithmetic(), "channel enumeration")
        .value("I", I, "fully irreducible channel except the bare interaction")
        .value("T", T, "particle-hole channel")
        .value("U", U, "particle-hole exchange channel")
        .value("S", S, "particle-particle channel")
        .value("TC", TC, "particle-hole counter channel")
        .value("UC", UC, "particle-hole exchange counter channel");

    py::class_<vertex4>(m, "vertex4")
        .def(py::init<>())
        .def("Build", &vertex4::Build, "level"_a, "order"_a, "Kidx"_a, "Tidx"_a,
             "chan"_a, "side"_a)
        .def("TauNum", &vertex4::TauNum)
        .def("LoopNum", &vertex4::LoopNum)
        .def_readwrite("Tpair", &vertex4::Tpair)
        .def_readwrite("Weight", &vertex4::Weight)
        .def_readwrite("Channel", &vertex4::Channel)
        .def_readwrite("Level", &vertex4::Level)
        .def_readwrite("Side", &vertex4::Side)
        .def_readwrite("Order", &vertex4::Order)
        .def_readwrite("Tidx", &vertex4::Tidx)
        .def_readwrite("Kidx", &vertex4::LoopIdx)
        .def_readwrite("G", &vertex4::G)
        .def_readwrite("UST", &vertex4::_UST);

    py::class_<bubble>(m, "bubble")
        .def(py::init<>())
        .def_readwrite("Channel", &bubble::Channel)
        .def_readwrite("LVer", &bubble::LVer)
        .def_readwrite("RVer", &bubble::RVer)
        .def_readwrite("Map", &bubble::Map);
  }

  {
    using namespace mc;
    // py::class_<markov>(m, "markov").def(py::init<>());
    // .def("ChangeTau", &markov::ChangeTau);
  }
}