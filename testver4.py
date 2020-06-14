import parquetMC as MC

chan = MC.channel

for o in range(1, 9):
    ver4 = MC.vertex4()
    ver4.Build(level=0, order=o, Kidx=0, Tidx=0, chan=[
        chan.T, chan.U, chan.S, chan.TC, chan.UC], side=1)
    print(o, " ", len(ver4.Tpair))
    # print(ver4.Weight[0])
