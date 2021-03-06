#!/usr/bin/env python3
from utility.IO import *
from utility.plot import *
import utility.fourier as fourier


def PlotSigmaW(SigmaT, MomGrid, idx, Save=True):
    SigmaW, Spec = Fourier.SpectralT2W(SigmaT[idx, :])
    # C0 = SigmaT[idx, 0]+SigmaT[idx, -1]
    SigmaWp = Fourier.naiveT2W(SigmaT[idx, :])

    _, (ax1, ax2) = plt.subplots(1, 2)
    # ax.plot(Freq, Spec[idx, :], "k--",
    #         label="k={0}, spectral".format(Grid.MomGrid[idx]))
    k = MomGrid[idx]/Para.kF
    ax1.plot(phyFreq, SigmaW.real, "r-",
             label="Spectral Fourier")
    ax1.plot(phyFreq, SigmaWp.real, "b--",
             label="Naive Fourier")
    # ax1.plot(phyFreq, -C0/phyFreq, "g--",
    #          label="$k/k_F={0:.4f}$, tail".format(k))
    # ax1.plot(phyFreq, (-1/(1.0j*phyFreq)).imag, "g--",
    #          label="$k/k_F={0:.4f}$, tail".format(k))

    # ax1.plot(phyFreq, PolarW.real, "bo",
    #          label="$k/k_F={0}$, spectral".format(k))
    # ax1.plot(phyFreq, PolarWp.real, "b--",
    #          label="$k/k_F={0}$, naive".format(k))

    # ax1.set_ylim([-0.12, 0.12])

    SigmaTspectral, _ = Fourier.SpectralW2T(SigmaW)
    SigmaTnaive = Fourier.naiveW2T(SigmaWp)
    # ax2.plot(TauGrid, Dynamic[idx, :], "ko", markersize=3,
    #          label="MC data")
    ax2.plot(TauGrid, Dynamic[idx, :], "ko", markersize=3,
             label="Exact")
    ax2.plot(TauGrid, SigmaTspectral.real, "r--",
             label="Spectral Fourier")
    ax2.plot(TauGrid, SigmaTnaive.real, "b--",
             label="Naive Fourier")

    # ax1.set_ylim([1.0e-6, 0.12])
    # ax2.set_ylim([0.004, 0.012])

    # ax1.set_yscale("log")
    # ax2.set_yscale("log")

    ax1.set_xlabel("$i\\omega_n$")
    ax1.set_ylabel("$-\\Sigma(k, i\\omega_n)$")
    ax2.set_xlabel("$\\tau$")
    ax2.set_ylabel("$-\\Sigma(k, \\tau)$")
    ax2.yaxis.set_label_position("right")
    ax2.yaxis.tick_right()

    ax1.legend(loc=1, frameon=False, fontsize=size)
    ax2.legend(loc=1, frameon=False, fontsize=size)
    # plt.title(f"$k/k_F={k:.4f}$")
    # plt.grid()
    plt.tight_layout()
    plt.savefig(f"k={k}.pdf")
    if Save:
        plt.savefig("SigmaW.pdf")
    else:
        plt.show()


if __name__ == "__main__":

    Para = param()
    Order = range(0, Para.Order+1)

    MaxFreq = 1024
    Freq = np.array(range(0, MaxFreq))
    phyFreq = (Freq*2.0+1.0)*np.pi/Para.Beta  # the physical frequency

    shape = (Para.Order+1, Para.MomGridSize, Para.TauGridSize)
    Data, Norm, Step, Grids = LoadFile("./Data", "sigma_pid[0-9]+.dat", shape)

    TauGrid = Grids["TauGrid"]
    MomGrid = Grids["KGrid"]

    Fourier = fourier.fourier(TauGrid, phyFreq, Para.Beta)
    Fourier.InitializeKernel(100.0, 1024, "Fermi", 1.0e-13)

    # Dynamic, DynErr = Estimate(
    #     Data, Norm, lambda d: np.sum(d[1:Para.Order+1, ...], axis=0))
    Dynamic, DynErr = Estimate(
        Data, Norm, lambda d: np.sum(d[2:3, ...], axis=0))

    arr = np.amin(abs(MomGrid-Para.kF))
    kFidx = np.where(abs(arr - abs(MomGrid-Para.kF)) < 1.0e-20)[0][0]
    print(kFidx)

    PlotSigmaW(Dynamic, MomGrid, 0, False)
    # PlotDataK(SigmaW, MaxFreq, Freq, False)
