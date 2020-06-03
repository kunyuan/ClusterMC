import numpy as np
MaxLoopNum = 8
I, T, U, S, TC, UC, SC = range(7)
IN, OUT = 0, 1
INL, OUTL, INR, OUTR = 0, 1, 2, 3
LEFT, RIGHT = 1, 2


def getK(loopidx):
    K = np.zeros(MaxLoopNum)
    K[loopidx] = 1
    return K
