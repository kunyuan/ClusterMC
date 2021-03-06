#define FMT_HEADER_ONLY
#include "abort.h"
#include "fmt/format.h"
#include "grid.h"
#include "markov.h"
#include "rng.h"
#include "timer.h"
#include "utility.h"
#include "utility/logger.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace mc;
void InitPara();
void InitVar();
void MonteCarlo();

// Global variable
parameter Para;        // global parameters
diag::propagator Prop; // global progator
variable Var;
void InitPara(), InitVar();

const string HelpStr = "Two parameters: PID Seed";

int main(int argc, const char *argv[]) {
  // take two parameters: PID and Seed
  if (argc > 1) {
    Para.PID = atoi(argv[1]);
    rng::randomize(Para.PID);
  } else
    Para.PID = rng::randomize(); // use the random_device of the system to seed

  ASSERT_ALLWAYS(Para.PID >= 0, "PID must be positive integer!");

  //// initialize the global log configuration   /////////////
  string LogFile = "_" + to_string(Para.PID) + ".log";
  LOGGER_CONF(LogFile, "MC", Logger::file_on | Logger::screen_on, INFO, INFO);

#ifdef NDEBUG
  LOG_INFO("NDEBUG is OFF. e.g, Turn off Range checking ...");
#else
  LOG_INFO("DEBUG mode is ON. e.g, Turn on Range checking ...");
#endif

  InitPara(); // initialize global parameters

  markov Markov;
  // InterruptHandler Interrupt;

  timer ReweightTimer, PrintTimer, SaveTimer, MessageTimer;
  PrintTimer.start();
  SaveTimer.start();
  MessageTimer.start();
  ReweightTimer.start();

  LOG_INFO("Loading Weight ...")
  Markov.Weight.LoadFile();
  InitVar(); // initialize MC variables
  Var.CurrAbsWeight = fabs(Markov.Weight.Evaluate(Var.CurrOrder));

  // Markov.Weight.Test();

  /////////////  Benchmark ////////////////////////////
  // for (int order = 1; order <= Para.Order; ++order) {
  //   Markov.Weight.Benchmark(order, 10000);
  // }
  // exit(0);
  //////////////////////////////////////////////////////

  LOG_INFO("Start simulation ...");
  int Block = 0;
  while (Block < Para.TotalStep) {
    Block++;

    for (int i = 0; i < 1000000; i++) {
      Var.Counter++;

      double x = rng::urn();
      if (x < 1.0 / 5.0) {
        Markov.ChangeOrder();
      } else if (x < 2.0 / 5.0) {
        Markov.ChangeMomentum();
      } else if (x < 3.0 / 5.0) {
        Markov.ChangeExtMomentum();
      } else if (x < 4.0 / 5.0) {
        Markov.ChangeTau();
      } else if (x < 5.0 / 5.0) {
        Markov.ChangeExtTau();
      }

      // cout << Var.LoopMom[0][0] << ", " << Var.LoopMom[0][1] << ", "
      //      << Var.LoopMom[0][2] << endl;
      // Markov.Weight.Test();

      if (i % 8 == 0)
        // fast operations
        Markov.Weight.Measure();

      if (i % 1000 == 0) {
        // slow operations
        if (PrintTimer.check(Para.PrintTimer)) {
          Markov.Weight.Test();
          Markov.PrintDeBugMCInfo();
          Markov.PrintMCInfo();
          LOG_INFO(ProgressBar((double)Block / Para.TotalStep));
        }

        if (SaveTimer.check(Para.SaveTimer)) {
          // Interrupt.Delay(); // the process can not be killed in saving
          Markov.Weight.SaveToFile();
          // Interrupt.Resume(); // after this point, the process can be killed
        }

        if (ReweightTimer.check(Para.ReweightTimer)) {
          Markov.AdjustGroupReWeight();
          Para.ReweightTimer *= 1.5;
        }

        if (MessageTimer.check(Para.MessageTimer)) {
          LOG_INFO("Loading Weight...")
          if (BoldG)
            Prop.LoadGreen();
          // Markov.Weight.LoadFile();
        }
      }
    }
  }

  Markov.PrintMCInfo();
  // Interrupt.Delay(); // the process can not be killed in saving
  Markov.Weight.SaveToFile();
  // Interrupt.Resume(); // after this point, the process can be killed

  LOG_INFO("Simulation is ended!");

  return 0;
}

void InitPara() {
  ifstream File;
  File.open("parameter", ios::in);
  ASSERT_ALLWAYS(File.is_open(), "Can not load parameters! \n");
  // parameters
  int dim, spin;
  auto paraStream = GetLine(File);
  paraStream >> Para.Order >> Para.Beta >> Para.Rs >> Para.Mass2 >>
      Para.Lambda >> Para.Charge2 >> dim >> spin >> Para.TotalStep;
  ASSERT_ALLWAYS(dim == D && spin == SPIN, "Dimension or SPIN doesn't match!");

  // grid information
  int TauSize, KSize, AngSize;
  double MaxK;
  auto gridStream = GetLine(File);
  gridStream >> TauSize >> KSize >> AngSize >> MaxK;

  // Timer information
  auto timerStream = GetLine(File);
  timerStream >> Para.PrintTimer >> Para.SaveTimer >> Para.ReweightTimer >>
      Para.MessageTimer;

  // ReWeight information
  auto reweightStream = GetLine(File);
  Para.ReWeight.resize(Para.Order + 1);
  for (auto &w : Para.ReWeight)
    reweightStream >> w;

  File.close();

  //// initialize the global parameter //////////////////////
  double Kf;
  if (D == 3) {
    Kf = pow(9.0 * π / 4.0, 1.0 / 3.0) / Para.Rs; // 3D
  } else if (D == 2) {
    Kf = sqrt(2.0) / Para.Rs; // 2D
  } else {
    ABORT(fmt::format("Dimension {} has not yet been implemented!", D));
  }
  Para.Kf = Kf;
  Para.Ef = Kf * Kf;
  Para.Mu = Para.Ef;
  Para.Nf = Kf / (4.0 * π * π) * SPIN;
  MaxK *= Kf;

  // scale all energy with E_F
  Para.Beta /= Para.Ef;

  LOG_INFO("Inverse Temperature: " << Para.Beta << "\n"
                                   << "r_s: " << Para.Rs << "\n"
                                   << "Fermi Mom: " << Para.Kf << "\n"
                                   << "Fermi Energy: " << Para.Ef << "\n"
                                   << "Lambda: " << Para.Lambda << "\n");

  LOG_INFO("PrintTimer: " << Para.PrintTimer << "\n"
                          << "SaveTimer: " << Para.SaveTimer << "\n"
                          << "ReWeightTimer: " << Para.ReweightTimer << "\n"
                          << "MessageTimer: " << Para.MessageTimer << "\n");

  // initialize grids
  Para.TauGrid.build(Para.Beta, TauSize, 6.0 / Para.Ef);
  Para.AngleGrid.build({-1.0, 1.0}, AngSize);

  Para.FermiKGrid.build(Para.Kf, MaxK, KSize, sqrt(1.0 / Para.Beta) * 2.0);
  Para.BoseKGrid.build(Para.Kf, MaxK, KSize, sqrt(1.0 / Para.Kf));

  if (BoldG)
    Prop.LoadGreen();
}

void InitVar() {
  // initialize group
  Var.Counter = 0;
  // Var.CurrGroup = &Groups[0];
  Var.CurrOrder = 0;

  // initialize momentum variables
  for (auto &mom : Var.LoopMom)
    for (int i = 0; i < D; i++)
      mom[i] = rng::urn(0.0, Para.Kf / sqrt(D));

  for (auto &t : Var.Tau)
    t = rng::urn(0.0, Para.Beta);

  // reference tau, it should not be updated
  Var.Tau[0] = 0.0;

  // Set the potential ExtTauBin
  Var.CurrExtTauBin = 0;
  Var.Tau[MaxTauNum - 1] = Para.TauGrid.grid[Var.CurrExtTauBin];

  if (DiagType == GAMMA) {
    Var.CurrExtMomBin = 0;
    for (int i = 0; i < 4; ++i)
      Var.LoopMom[i].setZero();
    Var.LoopMom[INL][0] = Para.Kf;
    Var.LoopMom[OUTL][0] = Para.Kf;

    Var.CurrExtAngBin = 0;
    double theta = acos(Para.AngleGrid.grid[Var.CurrExtAngBin]);
    Var.LoopMom[INR][0] = Para.Kf * cos(theta);
    Var.LoopMom[INR][1] = Para.Kf * sin(theta);

    Var.LoopMom[OUTR] = Var.LoopMom[INR];
  } else if (DiagType == SIGMA || DiagType == POLAR || DiagType == DELTA) {
    Var.CurrExtMomBin = 0;
    Var.LoopMom[0].setZero();
    if (DiagType == POLAR)
      Var.LoopMom[0][0] = Para.BoseKGrid.grid[Var.CurrExtMomBin];
    else
      Var.LoopMom[0][0] = Para.FermiKGrid.grid[Var.CurrExtMomBin];
  }
}
